/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 18:26:33 by aroullea          #+#    #+#             */
/*   Updated: 2025/05/05 19:07:15 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc_redirection(t_command *current, t_mini *mini)
{
	int	null_fd;

	if ((current->next == NULL)
		|| (current->next != NULL && current->next->check_here_doc == FALSE))
		duplicate_fd(current->here_doc_fd, STDIN_FILENO, mini, current);
	else
	{
		null_fd = open("/dev/null", O_RDONLY);
		duplicate_fd(null_fd, STDIN_FILENO, mini, current);
		close(null_fd);
	}
	close(current->here_doc_fd);
	current->here_doc_fd = -1;
	if (current->next != NULL && current->next->check_here_doc == TRUE)
	{
		null_fd = open("/dev/null", O_RDONLY);
		duplicate_fd(null_fd, STDOUT_FILENO, mini, current);
		close(null_fd);
	}
	if (current->next != NULL && current->next->check_here_doc == FALSE)
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

	errno = 0;
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
		check_directory(filename, mini);
		check_no_access(filename, errno_code, mini);
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
		check_directory(current->file[i], mini);
		check_no_access(current->file[i], errno_code, mini);
		no_such_file(current->file[i], mini);
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
		check_directory(filename, mini);
		check_no_access(filename, errno_code, mini);
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
