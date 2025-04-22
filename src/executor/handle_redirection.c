/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 18:26:33 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/16 20:35:17 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_file(t_mini *mini, char *filename, int flags, mode_t mode)
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

static void	duplicate_fd(t_mini *mini, int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
	{
		free_exit(mini);
		exit(EXIT_FAILURE);
	}
}

void	here_doc_redirection(t_command *current, t_mini *mini)
{
	(void)mini;
	if (dup2(current->here_doc_fd, STDIN_FILENO) == -1)
		write(2, "here_doc : dup2 error\n", 21);
	close(current->here_doc_fd);
	current->here_doc_fd = -1;
	if (current->next != NULL)
	{
		dup2(current->pipe_fd[1], STDOUT_FILENO);
		close(current->pipe_fd[1]);
	}
}

static void	handle_append(t_command *current, t_mini *mini, int *j)
{
	int		fd;
	int		i;
	int		flags;
	char	*filename;

	i = *j;
	filename = current->file[i];
	flags = O_WRONLY | O_APPEND | O_CREAT;
	if (access(filename, F_OK) != 0 || access(filename, W_OK) == 0)
	{
		fd = open_file(mini, current->file[i], flags, 0664);
		duplicate_fd(mini, fd, STDOUT_FILENO);
		close(fd);
	}
	else
	{
		print_file_error(current->file[i], ": Permission denied\n");
		exit (EXIT_FAILURE);
	}
}

static void	handle_input(t_command *current, t_mini *mini, int *j)
{
	int		file_fd;
	int		i;

	i = *j;
	errno = 0;
	if (access(current->file[i], F_OK | R_OK) == 0)
	{
		file_fd = open(current->file[i], O_RDONLY);
		if (file_fd == -1)
		{
			print_file_error(current->file[i], ": ");
			print_file_error(strerror(errno), "\n");
			free_commands(mini->cmds);
			exit(EXIT_FAILURE);
		}
		if (dup2(file_fd, STDIN_FILENO) == -1)
		{
			free_commands(mini->cmds);
			exit(errno);
		}
		close(file_fd);
	}
	else
	{
		if (errno == EACCES)
		{
			print_file_error(current->file[i], ": Permission denied\n");
			exit(EXIT_FAILURE);
		}
		else
		{
			print_file_error(current->file[i], ": No such file or directory\n");
			exit(EXIT_FAILURE);
		}
	}
}

static void	handle_output(t_command *current, t_mini *mini, int *j)
{
	int	file_fd;
	int	i;

	i = *j;
	if (access(current->file[i], F_OK) != 0)
	{
		file_fd = open(current->file[i], O_WRONLY | O_TRUNC | O_CREAT, 0664);
		if (file_fd == -1)
		{
			print_file_error(current->file[i], ": ");
			print_file_error(strerror(errno), "\n");
			free_commands(mini->cmds);
			exit(EXIT_FAILURE);
		}
	}
	else if (access(current->file[i], W_OK) == 0)
	{
		file_fd = open(current->file[i], O_WRONLY | O_TRUNC | O_CREAT, 0664);
		if (file_fd == -1)
		{
			print_file_error(current->file[i], ": ");
			print_file_error(strerror(errno), "\n");
			free_commands(mini->cmds);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		print_file_error(current->file[i], ": Permission denied\n");
		exit (EXIT_FAILURE);
	}
	if (dup2(file_fd, STDOUT_FILENO) == -1)
	{
		free_commands(mini->cmds);
		exit(errno);
	}
	close(file_fd);
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
