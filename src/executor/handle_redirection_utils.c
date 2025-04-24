/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:22:21 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/24 11:00:48 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_file(t_mini *mini, char *filename, int flags, mode_t mode)
{
	int	fd;

	fd = open(filename, flags, mode);
	if (fd == -1)
	{
		print_file_error(filename, ": ");
		print_file_error(strerror(errno), "\n");
		free_exit(mini);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	duplicate_fd(int oldfd, int newfd, t_mini *mini, t_command *current)
{
	if (dup2(oldfd, newfd) == -1)
	{
		write(2, "dup2 error\n", 11);
		close(oldfd);
		if ((current->next != NULL) && (current->pipe_fd[1] != -1))
		{
			close(current->pipe_fd[1]);
			current->pipe_fd[1] = -1;
		}
		free_exit(mini);
		exit(EXIT_FAILURE);
	}
}

void	check_directory(char *filename, t_mini *mini)
{
	struct stat	statbuf;

	if (lstat(filename, &statbuf) == 0)
	{
		if (S_ISDIR(statbuf.st_mode))
		{
			print_executor_error("Is a directory", filename);
			free_exit(mini);
			exit (EXIT_FAILURE);
		}
	}
}

void	check_no_access(char *filename, int errno_code, t_mini *mini)
{
	if (errno_code == EACCES)
	{
		print_file_error(filename, ": Permission denied\n");
		free_exit(mini);
		exit(EXIT_FAILURE);
	}
}

void	no_such_file(char *filename, t_mini *mini)
{
	print_file_error(filename, ": No such file or directory\n");
	free_exit(mini);
	exit(EXIT_FAILURE);
}
