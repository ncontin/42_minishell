/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 18:26:33 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/03 19:03:55 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_redirection(t_command *current, t_mini *mini)
{
	int	file_fd;

	if (current->operator == INPUT)
	{
		if (access(current->file, F_OK | R_OK) == 0)
		{
			file_fd = open(current->file, O_RDONLY);
			if (file_fd == -1)
			{
				close_fd(current->pipe_fd);
				free_commands(mini->cmds);
				exit(errno);
			}
			if (dup2(file_fd, STDIN_FILENO) == -1)
			{
				close_fd(current->pipe_fd);
				free_commands(mini->cmds);
				exit(errno);
			}
			close(file_fd);
		}
	}
	if (current->operator == OUTPUT)
	{
		file_fd = open(current->file, O_WRONLY | O_TRUNC | O_CREAT, 0664);
		if (file_fd == -1)
		{
			close_fd(current->pipe_fd);
			free_commands(mini->cmds);
			exit(errno);
		}
		if (dup2(file_fd, STDOUT_FILENO) == -1)
		{
			close_fd(current->pipe_fd);
			free_commands(mini->cmds);
			exit(errno);
		}
		close(file_fd);
	}
}
