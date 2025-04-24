/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:48:42 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/24 10:58:53 by aroullea         ###   ########.fr       */
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

void	error_dup2_executor(t_mini *mini, int error_code, int *prev_fd)
{
	write(STDERR_FILENO, "executor :", 10);
	write(STDERR_FILENO, strerror(error_code), ft_strlen(strerror(error_code)));
	write(STDERR_FILENO, "\n", 1);
	if (*prev_fd != -1)
		close(*prev_fd);
	free_exit(mini);
	exit(EXIT_FAILURE);
}

void	error_open_executor(t_mini *mini, int error_code)
{
	write(STDERR_FILENO, "executor :", 10);
	write(STDERR_FILENO, strerror(error_code), ft_strlen(strerror(error_code)));
	write(STDERR_FILENO, "\n", 1);
	free_exit(mini);
	exit(EXIT_FAILURE);
}

void	print_executor_error(char *msg, char *arg)
{
	write(STDERR_FILENO, arg, ft_strlen(arg));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\n", 1);
}

void	error_path(t_mini *mini, char **envp, int error_code, t_command *cmd)
{
	if (error_code == EACCES)
	{
		print_executor_error("Permission denied", cmd->argv[0]);
		clean_exit(mini, envp, 126);
	}
	else
	{
		print_executor_error(": command not found\n", cmd->argv[0]);
		clean_exit(mini, envp, 127);
	}
}
