/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:48:42 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/18 17:09:51 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_pid_executor(t_mini *mini, t_command *current, int *prev_fd)
{
	mini->error = errno;
	write(STDERR_FILENO, "executor: ", 10);
	write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
	write(STDERR_FILENO, "\n", 1);
	close(current->pipe_fd[0]);
	close(current->pipe_fd[1]);
	if (*prev_fd != -1)
		close(*prev_fd);	
}
