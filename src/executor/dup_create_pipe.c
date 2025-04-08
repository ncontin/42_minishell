/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_create_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:20:41 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/08 17:02:04 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	duplicate_pipes(t_command *current, int *prev_fd, t_mini *mini)
{
	if (current->next != NULL)
	{
		if (dup2(current->pipe_fd[1], STDOUT_FILENO) == -1)
		{
			close_fd(current->pipe_fd);
			free_commands(mini->cmds);
			write(2, "dup2 error\n", 10);
			return ;
		}
		close(current->pipe_fd[1]);
	}
	if (*prev_fd != -1)
	{
		if (dup2(*prev_fd, STDIN_FILENO) == -1)
		{
			free_commands(mini->cmds);
			write(2, "dup2 error\n", 10);
			return ;
		}
		close(*prev_fd);
	}
}

void	create_pipe(t_command *current, t_mini *mini)
{
	if (current->next != NULL)
	{
		if (pipe(current->pipe_fd) == -1)
		{
			close_fd(current->pipe_fd);
			free_commands(mini->cmds);
			return ;
		}
	}
}
