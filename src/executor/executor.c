/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:52:47 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/02 12:20:45 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_cmd(t_command *current, char **envp, t_mini *mini)
{
	char	**unix_path;
	char	*path;
	int		i;

	i = 0;
	if (access(current->argv[0], X_OK) == 0)
	{
		if (execve(current->argv[0], current->argv, envp) == -1)
		{
			free_commands(mini->cmds);
			exit(errno);
		}
	}
	else
	{
		unix_path = get_unix_path(mini->lst_env->envp);
		while (unix_path[i])
		{
			path = copy_command(unix_path[i], current->argv[0]);
			if (access(path, X_OK) == 0)
			{
				if (execve(path, current->argv, envp) == -1)
				{
					free_commands(mini->cmds);
					exit(errno);
				}
			}
			free(path);
			i++;
		}
		exit(127);
	}
}

static void	handle_redirection(t_command *current, t_mini *mini)
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
				exit (errno);
			}
			if (dup2(file_fd, STDIN_FILENO) == -1)
			{
				close_fd(current->pipe_fd);
				free_commands(mini->cmds);
				exit (errno);
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
			exit (errno);
		}
		if (dup2(file_fd, STDOUT_FILENO) == -1)
		{
			close_fd(current->pipe_fd);
			free_commands(mini->cmds);
			exit (errno);
		}
		close(file_fd);
	}
}

void	executor(t_mini *mini)
{
	t_command	*current;
	int			status;

	current = mini->cmds;
	while (current != NULL)
	{
		if (current->next != NULL) //check if there is a pipe
		{
			if (pipe(current->pipe_fd) == -1)
			{
				close_fd(current->pipe_fd);
				free_commands(mini->cmds);
				return ;
			}
		}
		current->pid = fork();
		if (current->pid < 0)
		{
			close_fd(current->pipe_fd);
			free_commands(mini->cmds);
			write(2, "fork error\n", 10);
			return ;
		}
		if (current->pid == 0) //child process
		{
			if (current->next != NULL) //if there is a pipe
			{
				if (dup2(current->pipe_fd[1], STDOUT_FILENO) == -1)
				{
					close_fd(current->pipe_fd);
					free_commands(mini->cmds);
					write(2, "dup2 error\n", 10);
					return ;
				}
				close(current->pipe_fd[1]);
			}
			if (current->prev != NULL) //if there was a pipe
			{
				if (dup2(current->prev->pipe_fd[0], STDIN_FILENO) == -1)
				{
					close_fd(current->pipe_fd);
					free_commands(mini->cmds);
					write(2, "dup2 error\n", 10);
					return ;
				}
				close(current->prev->pipe_fd[0]);
				close(current->prev->pipe_fd[1]);
			}
			if (current->operator != NONE) //check if there is a redirection
				handle_redirection(current, mini);
			else if (current->next != NULL) //there is a pipe but no redirection
				close(current->pipe_fd[0]);
			execute_cmd(current, mini->lst_env->envp, mini);
		}
		else if (current->pid > 0)
		{
			current = current->next;
		}
	}
	while (wait(&status) > 0)
		;
}
