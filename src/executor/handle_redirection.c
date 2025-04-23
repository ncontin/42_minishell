/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 18:26:33 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/23 06:46:55 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc_redirection(t_command *current, t_mini *mini)
{
	(void)mini;
	duplicate_fd(current->here_doc_fd, STDIN_FILENO, mini, current);
	close(current->here_doc_fd);
	current->here_doc_fd = -1;
	if (current->next != NULL)
	{
		duplicate_fd(current->pipe_fd[1], STDOUT_FILENO, mini, current);
		close(current->pipe_fd[1]);
		current->pipe_fd[1] = -1;
	}
}

static void	handle_append(t_command *current, t_mini *mini, int *i)
{
	int			fd;
	int			flags;
	int			errno_code;
	char		*filename;

	filename = current->file[*i];
	flags = O_WRONLY | O_APPEND | O_CREAT;
	if (access(filename, F_OK) != 0 || access(filename, W_OK) == 0)
	{
		fd = open_file(mini, filename, flags, 0664);
		duplicate_fd(fd, STDOUT_FILENO, mini, current);
		close(fd);
	}
	else
	{
		errno_code = errno;
		check_directory(filename);
		if (errno_code == EACCES)
		{
			print_file_error(filename, ": Permission denied\n");
			exit(EXIT_FAILURE);
		}
	}
}

static void	handle_input(t_command *current, t_mini *mini, int *j)
{
	int		fd;
	int		i;
	int		errno_code;

	i = *j;
	errno = 0;
	if (access(current->file[i], F_OK | R_OK) == 0)
	{
		fd = open_file(mini, current->file[i], O_RDONLY, 0664);
		duplicate_fd(fd, STDIN_FILENO, mini, current);
		close (fd);
	}
	else
	{
		errno_code = errno;
		check_directory(current->file[i]);
		if (errno_code == EACCES)
		{
			print_file_error(current->file[i], ": Permission denied\n");
			exit(EXIT_FAILURE);
		}
		print_file_error(current->file[i], ": No such file or directory\n");
		exit(EXIT_FAILURE);
	}
}

static void	handle_output(t_command *current, t_mini *mini, int *i)
{
	int		fd;
	int		flags;
	int		errno_code;
	char	*filename;

	errno = 0;
	filename = current->file[*i];
	flags = O_WRONLY | O_TRUNC | O_CREAT;
	if (access(filename, F_OK) != 0 || access(filename, W_OK) == 0)
	{
		fd = open_file(mini, filename, flags, 0664);
		duplicate_fd(fd, STDOUT_FILENO, mini, current);
		close(fd);
	}
	else
	{
		errno_code = errno;
		check_directory(filename);
		if (errno_code == EACCES)
		{
			print_file_error(filename, ": Permission denied\n");
			exit(EXIT_FAILURE);
		}
	}
}

void	handle_redirection(t_command *current, t_mini *mini)
{
	int	i;

	i = current->nb_operator - 1;
	while (i >= 0)
	{
		if (current->operator[i] == HEREDOC)
		{
			here_doc_redirection(current, mini);
			break ;
		}
		i--;
	}
	i = 0;
	while (i < current->nb_operator)
	{
		if (current->operator[i] == INPUT)
			handle_input(current, mini, &i);
		else if (current->operator[i] == OUTPUT)
			handle_output(current, mini, &i);
		else if (current->operator[i] == APPEND)
			handle_append(current, mini, &i);
		i++;
	}
}
