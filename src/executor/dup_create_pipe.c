/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_create_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:20:41 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/15 11:49:27 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	duplicate_pipes(t_command *current, int *prev_fd, t_mini *mini)
{
	int	null_fd;

	(void)mini;
	if (current->next != NULL && current->next->check_here_doc == FALSE)
	{
		if (current->check_here_doc == FALSE)
		{
			if (current->next != NULL)
			{
				if (dup2(current->pipe_fd[1], STDOUT_FILENO) == -1)
				{
					write(2, "dup2 error\n", 10);
					return ;
				}
				close(current->pipe_fd[1]);
			}
			if (*prev_fd != -1)
			{
				if (dup2(*prev_fd, STDIN_FILENO) == -1)
				{
					write(2, "dup2 error\n", 10);
					return ;
				}
				close(*prev_fd);
			}
		}
	}
	else if (current->check_here_doc == FALSE && current->next != NULL 
			&& current->next->check_here_doc && current->nb_operator == 0)
	{
		if (*prev_fd != -1)
		{
			if (dup2(*prev_fd, STDIN_FILENO) == -1)
			{
				write(2, "dup2 error\n", 10);
				return ;
			}
			close(*prev_fd);
		}
		null_fd = open("/dev/null", O_WRONLY);
		dup2(null_fd, STDOUT_FILENO);
		close(null_fd);
	}
	else
	{
		if (*prev_fd != -1)
		{
			if (dup2(*prev_fd, STDIN_FILENO) == -1)
			{
				write(2, "dup2 error\n", 10);
				return ;
			}
			close(*prev_fd);
		}
	}
}

void	create_pipe(t_command *current, t_mini *mini)
{
	(void)mini;
	
	if (current->next != NULL && (current->next->check_here_doc == FALSE))
	{
		if (pipe(current->pipe_fd) == -1)
		{
			close_fd(current->pipe_fd);
			return ;
		}
	}
}
