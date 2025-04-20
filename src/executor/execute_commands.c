/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 18:31:31 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/17 12:32:07 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_path_and_exec(t_mini *mini, t_command *cmd, char **envp,
		char **unix_path)
{
	int		i;
	char	*path;

	i = 0;
	while (unix_path[i])
	{
		path = copy_command(unix_path[i], cmd->argv[0]);
		if (access(path, X_OK) == 0)
		{
			if (execve(path, cmd->argv, envp) == -1)
			{
				write(STDERR_FILENO, "execve error\n", 13);
				free(path);
				free_array(unix_path);
				clean_exit(mini, envp, 1);
			}
		}
		free(path);
		i++;
	}
}

static void	find_path(t_command *current, char **envp, t_mini *mini)
{
	char	**unix_path;

	unix_path = get_unix_path(mini->lst_env->envp);
	if (unix_path == NULL)
	{
		print_executor_error(":No such file or directory\n", current->argv[0]);
		clean_exit(mini, envp, 127);
	}
	get_path_and_exec(mini, current, envp, unix_path);
	if (errno == ENOENT)
		print_executor_error(": command not found\n", current->argv[0]);
	free_array(unix_path);
	clean_exit(mini, envp, 127);
}

static void	check_special_cases(t_command *cmd, char **envp, t_mini *mini)
{
	if (!cmd->argv)
		clean_exit(mini, envp, 0);
	else if (cmd->argv[0][0] == '\0')
	{
		write(STDERR_FILENO, "Command \'\' not found\n", 21);
		clean_exit(mini, envp, 127);
	}
	if (cmd->argv[0][0] == '$' && cmd->argv[0][1] == '\0')
	{
		write(STDERR_FILENO, "$ : command not found\n", 23);
		clean_exit(mini, envp, 127);
	}
}

static void	handle_path(t_command *current, char **envp, t_mini *mini)
{
	struct stat	statbuf;

	if (access(current->argv[0], F_OK) != 0)
	{
		print_executor_error(strerror(errno), current->argv[0]);
		clean_exit(mini, envp, 127);
	}
	errno = 0;
	if (access(current->argv[0], X_OK) == 0)
	{
		if (lstat(current->argv[0], &statbuf) == 0)
		{
			if (S_ISDIR(statbuf.st_mode))
			{
				print_executor_error(": Is a directory\n", current->argv[0]);
				clean_exit(mini, envp, 126);
			}
			if (execve(current->argv[0], current->argv, envp) == -1)
			{
				write(STDERR_FILENO, "execve error\n", 13);
				clean_exit(mini, envp, errno);
			}
		}
	}
	error_path(mini, envp, errno, current);
}

void	execute_cmd(t_command *cmd, char **envp, t_mini *mini)
{
	check_special_cases(cmd, envp, mini);
	if (is_builtin(cmd->argv[0]))
	{
		execute_builtin(mini, cmd->argv);
		clean_exit(mini, envp, mini->exit_code);
	}
	if (cmd->argv[0][0] == '/'
			|| (cmd->argv[0][0] == '.' && cmd->argv[0][1] == '/'))
		handle_path(cmd, envp, mini);
	else
		find_path(cmd, envp, mini);
}
