/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:52:47 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/07 19:04:41 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_process(t_command *current, int *prev_fd, t_mini *mini)
{
	char	**envp;

	duplicate_pipes(current, prev_fd, mini);
	if (current->operator!= NONE)
		handle_redirection(current, mini);
	else if (current->next != NULL)
		close(current->pipe_fd[0]);
	envp = get_envp_array(mini->lst_env);
	execute_cmd(current, envp, mini);
}

static void	parent_process(int *prev_fd, t_command *current)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (current->next != NULL)
	{
		close(current->pipe_fd[1]);
		*prev_fd = current->pipe_fd[0];
	}
}

static t_bool	handle_start(t_command *current, t_mini *mini)
{

	if (current->argv != NULL && current->argv[0] != NULL)
	{
		if (ft_strncmp(current->argv[0], "exit", 4) == 0
			&& current->next == NULL)
			ft_exit(mini, NULL);
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
	int	status;
	int	i;

	i = 0;
	while (i < fork_count)
	{
		if (waitpid(-1, &status, 0) == -1)
		{
			write(2, "waitpid error\n", 14);
			mini->error = 1;
		}
		i++;
	}
	if (i > 0)
	{
		if (WIFEXITED(status))
			mini->exit_code = WEXITSTATUS(status);
	}
	if (mini->error > 0)
	{
		free_all(mini);
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
			child_process(current, &prev_fd, mini);
		else if (current->pid > 0)
		{
			parent_process(&prev_fd, current);
			current = current->next;
		}
		fork_count++;
	}
	wait_children(mini, fork_count);
}
