/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:52:47 by aroullea          #+#    #+#             */
/*   Updated: 2025/05/06 08:56:48 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_error(t_mini *mini, int sig, int status)
{
	if (sig == SIGINT)
	{
		mini->exit_code = 128 + sig;
		printf("\n");
	}
	if (WIFEXITED(status))
		mini->exit_code = WEXITSTATUS(status);
}

static void	wait_children(t_mini *mini, int fork_count)
{
	int			i;
	int			sig;
	int			status;
	t_command	*current;

	i = 0;
	sig = 0;
	status = 0;
	current = mini->cmds;
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
		check_error(mini, sig, status);
}

static int	is_builtin_command(t_command *current)
{
	if (!current)
		return (0);
	if (current->prev || current->next)
		return (0);
	if (!current->argv || !current->argv[0])
		return (0);
	if (current->file)
		return (0);
	if (is_builtin(current->argv[0]))
		return (1);
	return (0);
}

static int	handle_start(t_command *current, t_mini *mini)
{
	if (current->next == NULL && current->prev == NULL)
	{
		if (current->argv != NULL && current->argv[0] == NULL)
			return (1);
	}
	if (is_builtin_command(current))
	{
		update_underscore(current, mini->envp_cp, mini);
		execute_builtin(mini, current->argv);
		return (1);
	}
	executor_signal();
	if (setup_here_docs(mini) == 1)
		return (1);
	precreate_files(current);
	return (0);
}

void	executor(t_mini *mini, t_command *current, int prev_fd, int fork_count)
{
	if (handle_start(current, mini))
		return ;
	if (current->next == NULL)
		update_underscore(current, mini->envp_cp, mini);
	while (current != NULL)
	{
		if (create_pipe(current, &prev_fd, mini))
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
			parent_process(&prev_fd, current);
			current = current->next;
			fork_count++;
		}
	}
	wait_children(mini, fork_count);
}
