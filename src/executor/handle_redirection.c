/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 18:26:33 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/13 19:06:08 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	append_operator(t_command *current, t_mini *mini, int *j)
{
	int	file_fd;
	int	i;

	i = *j;

	if (access(current->file[i], F_OK) != 0) 
	{
		file_fd = open(current->file[i], O_WRONLY | O_APPEND | O_CREAT, 0664);
		if (file_fd == -1)
		{
			write(STDERR_FILENO, current->file[i], ft_strlen(current->file[i]));
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
			write(STDERR_FILENO, "\n", 1);
			free_commands(mini->cmds);
			exit(EXIT_FAILURE);
		}
	}
	else if (access(current->file[i], W_OK) == 0)
	{
		file_fd = open(current->file[i], O_WRONLY | O_APPEND | O_CREAT, 0664);
		if (file_fd == -1)
		{
			write(STDERR_FILENO, current->file[i], ft_strlen(current->file[i]));
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
			write(STDERR_FILENO, "\n", 1);
			free_commands(mini->cmds);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		write(STDERR_FILENO, current->file[i], ft_strlen(current->file[i]));
		write(STDERR_FILENO, ": Permission denied\n", 20);
		exit (EXIT_FAILURE);
	}
	if (dup2(file_fd, STDOUT_FILENO) == -1)
	{
		free_commands(mini->cmds);
		exit(errno);
	}
	close(file_fd);
}

static void	input_operator(t_command *current, t_mini *mini, int *j)
{
	int	file_fd;
	int	i;

	i = *j;
	if (access(current->file[i], F_OK | R_OK) == 0)
	{
		file_fd = open(current->file[i], O_RDONLY);
		if (file_fd == -1)
		{
			write(STDERR_FILENO, current->file[i], ft_strlen(current->file[i]));
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
			write(STDERR_FILENO, "\n", 1);
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
		write(STDERR_FILENO, current->file[i], ft_strlen(current->file[i]));
		write(STDERR_FILENO, ": No such file or directory\n", 28);
		exit(EXIT_FAILURE);
	}
}

static void	output_operator(t_command *current, t_mini *mini, int *j)
{
	int	file_fd;
	int	i;

	i = *j;
	if (access(current->file[i], F_OK) != 0) 
	{
		file_fd = open(current->file[i], O_WRONLY | O_TRUNC | O_CREAT, 0664);
		if (file_fd == -1)
		{
			write(STDERR_FILENO, current->file[i], ft_strlen(current->file[i]));
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
			write(STDERR_FILENO, "\n", 1);
			free_commands(mini->cmds);
			exit(EXIT_FAILURE);
		}
	}
	else if (access(current->file[i], W_OK) == 0)
	{
		file_fd = open(current->file[i], O_WRONLY | O_TRUNC | O_CREAT, 0664);
		if (file_fd == -1)
		{
			write(STDERR_FILENO, current->file[i], ft_strlen(current->file[i]));
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
			write(STDERR_FILENO, "\n", 1);
			free_commands(mini->cmds);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		write(STDERR_FILENO, current->file[i], ft_strlen(current->file[i]));
		write(STDERR_FILENO, ": Permission denied\n", 20);
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

	i = 0;
	while (i < current->nb_operator)
	{
		if (current->operator[i] == HEREDOC)
			setup_here_doc(current, mini, &i);
		i++;
	}
	i = 0;
	while (i < current->nb_operator)
	{
		if (current->operator[i] == INPUT)
			input_operator(current, mini, &i);
		else if (current->operator[i] == OUTPUT)
			output_operator(current, mini, &i);
		else if (current->operator[i] == APPEND)
			append_operator(current, mini, &i);
		i++;
	}
}
