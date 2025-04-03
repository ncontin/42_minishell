/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:31:12 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/03 18:58:38 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_msg(char *message, int error)
{
	write(STDERR_FILENO, message, ft_strlen(message) + 1);
	write(STDERR_FILENO, "\n", 1);
	exit(error);
}

void	error_pid(t_command *current, t_mini *mini)
{
	close_fd(current->pipe_fd);
	free_commands(mini->cmds);
	write(2, "fork error\n", 10);
}
