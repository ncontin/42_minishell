/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:52:47 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/14 11:19:04 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_process(t_command *current, int *prev_fd, t_mini *mini)
{
	char	**envp;

	duplicate_pipes(current, prev_fd, mini);
	if (current->operator!= NONE)
		handle_redirection(current, mini);
	envp = get_envp_array(mini->lst_env);
	execute_cmd(current, envp, mini);
}

static void	parent_signal(int signo)
{
	if (signo == SIGINT)
		printf("\n");
}

static void	parent_process(int *prev_fd, t_command *current)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	if (*prev_fd != -1)
	{
		close(*prev_fd);
		*prev_fd = -1;
	}
	if (current->next != NULL)
	{
		close(current->pipe_fd[1]);
		*prev_fd = current->pipe_fd[0];
	}
}

static t_bool	handle_start(t_command *current, t_mini *mini)
{
	if (current->next == NULL && current->prev == NULL)
	{
		if (current->argv != NULL && current->argv[0] == NULL)
			return (TRUE);
	}
	if (current->argv != NULL && current->argv[0] != NULL)
	{
		if (current && !current->next && is_builtin(current->argv[0]))
		{
			if (current->file != NULL)
				return (FALSE);
			if (execute_builtin_parent(mini, current) == TRUE)
				return (TRUE);
		}
	}
	return (FALSE);
}

void	wait_children(t_mini *mini, int fork_count)
{
	int					status;
	int					i;
	int					sig;
	t_command			*current;
	struct sigaction	sa;

	i = 0;
	current = mini->cmds;
	while ((current != NULL) || (i < fork_count))
	{
		if (waitpid(current->pid, &status, 0) == -1)
		{
			write(2, "waitpid error\n", 14);
			mini->error = errno;
		}
		current = current->next;
		i++;
	}
	sa.sa_handler = parent_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	if (i > 0)
	{
		if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			if (sig == SIGINT)
				write(1, "\n", 1);
		}
		if (WIFEXITED(status))
			mini->exit_code = WEXITSTATUS(status);
	}
	if (mini->error > 0)
	{
		free_exit(mini);
		exit(mini->error);
	}
}

void	executor(t_mini *mini)
{
	t_command	*current;
	int			prev_fd;
	int			fork_count;

	current = mini->cmds;
	prev_fd = -1;
	fork_count = 0;
	if (handle_start(current, mini) == TRUE)
		return ;
	while (current != NULL)
	{
		create_pipe(current, mini);
		current->pid = fork();
		if (current->pid < 0)
		{
			mini->error = errno;
			write(2, "fork error\n", 11);
			break ;
		}
		else if (current->pid == 0)
		{
			if (current->next != NULL)
				close(current->pipe_fd[0]);
			child_process(current, &prev_fd, mini);
		}
		else if (current->pid > 0)
		{
			parent_process(&prev_fd, current);
			current = current->next;
		}
		fork_count++;
	}
	wait_children(mini, fork_count);
}
