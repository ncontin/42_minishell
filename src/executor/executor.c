/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:52:47 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/18 17:22:32 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_child_heredoc_fd(t_command *cmds, t_command *current)
{
	t_command	*commands;

	commands = cmds;
	while (commands != NULL)
	{
		if (commands->check_here_doc == TRUE)
		{
			if (current != commands && commands->here_doc_fd != -1)
			{
				close (commands->here_doc_fd);
				commands->here_doc_fd = -1;
			}
		}
		commands = commands->next;
	}
}

static void	close_parent_heredoc_fd(t_command *current)
{
	t_command	*commands;

	commands = current->prev;
	while (commands != NULL)
	{
		if (commands->check_here_doc == TRUE && commands->here_doc_fd != -1)
		{
			close (commands->here_doc_fd);
			commands->here_doc_fd = -1;
		}
		commands = commands->prev;
	}
}

static void	child_process(t_command *current, int *prev_fd, t_mini *mini)
{
	char	**envp;

	child_signal();
	if (current->next != NULL && current->next->check_here_doc == FALSE)
		close(current->pipe_fd[0]);
	close_child_heredoc_fd(mini->cmds, current);
	duplicate_pipes(current, prev_fd, mini);
	if (current->operator != NONE)
		handle_redirection(current, mini);
	envp = get_envp_array(mini->lst_env);
	execute_cmd(current, envp, mini);
}

static int	parent_process(int *prev_fd, t_command *current)
{
	if (*prev_fd != -1)
	{
		close(*prev_fd);
		*prev_fd = -1;
	}
	if (current->next != NULL && current->next->check_here_doc == FALSE)
	{
		close(current->pipe_fd[1]);
		*prev_fd = current->pipe_fd[0];
	}
	close_parent_heredoc_fd(current);
	return (0);
}

static int	handle_start(t_command *current, t_mini *mini)
{
	if (current->next == NULL && current->prev == NULL)
	{
		if (current->argv != NULL && current->argv[0] == NULL)
			return (1);
	}
	if (current->argv != NULL && current->argv[0] != NULL)
	{
		if (current && !current->next && is_builtin(current->argv[0]))
		{
			if (current->file != NULL)
				return (0);
			if (execute_builtin_parent(mini, current) == TRUE)
				return (1);
		}
	}
	executor_signal();
	if (setup_here_docs(mini) == 1)
		return (1);
	return (0);
}

void	wait_children(t_mini *mini, int fork_count)
{
	int			status;
	int			i;
	int			sig;
	t_command	*current;

	i = 0;
	sig = 0;
	current = mini->cmds;
	status = 0;
	while ((current != NULL) && (i < fork_count))
	{
		if (waitpid(current->pid, &status, 0) == -1)
		{
			write(2, "waitpid error\n", 14);
			mini->error = errno;
		}
		if (WIFSIGNALED(status))
			sig = WTERMSIG(status);
		current = current->next;
		i++;
	}
	if (i > 0)
	{
		if (sig == SIGINT)
		{
			mini->exit_code = 128 + sig;
			printf("\n");
		}
		if (WIFEXITED(status))
			mini->exit_code = WEXITSTATUS(status);
	}
}

void	executor(t_mini *mini, t_command *current, int prev_fd, int fork_count)
{
	if (handle_start(current, mini) == 1)
		return ;
	while (current != NULL)
	{
		if (create_pipe(current, &prev_fd, mini) == 1)
			break ;
		current->pid = fork();
		if (current->pid < 0)
		{
			error_pid_executor(mini, current, &prev_fd);
			break ;
		}
		else if (current->pid == 0)
			child_process(current, &prev_fd, mini);
		else
		{
			if (parent_process(&prev_fd, current) == 1)
				return ;
			current = current->next;
			fork_count++;
		}
	}
	wait_children(mini, fork_count);
}
