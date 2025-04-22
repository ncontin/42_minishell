/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_create_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:20:41 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/18 16:19:49 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_prev_fd(int *prev_fd, t_mini *mini)
{
	if (*prev_fd != -1)
	{
		if (dup2(*prev_fd, STDIN_FILENO) == -1)
			error_dup2_executor(mini, errno, prev_fd);
		close(*prev_fd);
		*prev_fd = -1;
	}
}

static void	handle_no_here_doc(t_command *current, int *prev_fd, t_mini *mini)
{
	if (current->next != NULL)
	{
		if (dup2(current->pipe_fd[1], STDOUT_FILENO) == -1)
		{
			close(current->pipe_fd[1]);
			current->pipe_fd[1] = -1;
			error_dup2_executor(mini, errno, prev_fd);
		}
		close(current->pipe_fd[1]);
		current->pipe_fd[1] = -1;
	}
	handle_prev_fd(prev_fd, mini);
}

void	duplicate_pipes(t_command *current, int *prev_fd, t_mini *mini)
{
	int	null_fd;

	if (current->next != NULL && current->next->check_here_doc == FALSE)
	{
		if (current->check_here_doc == FALSE)
			handle_no_here_doc(current, prev_fd, mini);
	}
	else if (current->check_here_doc == FALSE && current->next != NULL
		&& current->next->check_here_doc && current->nb_operator == 0)
	{
		handle_prev_fd(prev_fd, mini);
		null_fd = open("/dev/null", O_WRONLY);
		if (null_fd == -1)
			error_open_executor(mini, errno);
		if (dup2(null_fd, STDOUT_FILENO) == -1)
		{
			close(null_fd);
			error_dup2_executor(mini, errno, prev_fd);
		}
		close(null_fd);
	}
	else
		handle_prev_fd(prev_fd, mini);
}

int	create_pipe(t_command *current, int *prev_fd, t_mini *mini)
{
	if (current->next != NULL && (current->next->check_here_doc == FALSE))
	{
		if (pipe(current->pipe_fd) == -1)
		{
			mini->exit_code = errno;
			write(STDERR_FILENO, "executor: ", 10);
			write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
			write(STDERR_FILENO, "\n", 1);
			if (*prev_fd != -1)
				close(*prev_fd);
			return (1);
		}
	}
	return (0);
}
