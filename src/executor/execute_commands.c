/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 18:31:31 by aroullea          #+#    #+#             */
/*   Updated: 2025/05/03 12:05:44 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_path_and_exec(t_mini *mini, t_command *cmd, char **envp,
		char **unix_path)
{
	int		i;
	char	*path;

	i = 0;
	errno = 0;
	while (unix_path[i])
	{
		path = copy_command(unix_path[i], cmd->argv[0]);
		if (path == NULL)
			free_and_exit(mini, unix_path, envp);
		if (access(path, X_OK) == 0)
		{
			update_underscore_path(path, mini->envp_cp, mini);
			if (execve(path, cmd->argv, envp) == -1)
			{
				free_array(unix_path);
				handle_no_exec(cmd, envp, mini, errno);
				write(STDERR_FILENO, "execve error\n", 13);
				free_and_exit(mini, NULL, envp);
			}
		}
		free(path);
		i++;
	}
}

static void	find_path(t_command *current, char **envp, t_mini *mini)
{
	char	**unix_path;
	int		error_code;

	unix_path = get_unix_path(envp);
	if (unix_path == NULL || *unix_path == NULL)
	{
		free_array(unix_path);
		is_user_in_bin(mini, current, envp);
		print_executor_error("No such file or directory", current->argv[0]);
		clean_exit(mini, envp, 127);
	}
	get_path_and_exec(mini, current, envp, unix_path);
	error_code = errno;
	free_array(unix_path);
	handle_no_exec(current, envp, mini, error_code);
	clean_exit(mini, envp, 1);
}

static void	handle_path(t_command *current, char **envp, t_mini *mini)
{
	if (access(current->argv[0], F_OK) != 0)
	{
		print_executor_error(strerror(errno), current->argv[0]);
		clean_exit(mini, envp, 127);
	}
	errno = 0;
	if (access(current->argv[0], X_OK) == 0)
	{
		is_path_a_directory(current, envp, mini);
		if (execve(current->argv[0], current->argv, envp) == -1)
		{
			handle_no_exec(current, envp, mini, errno);
			write(STDERR_FILENO, "execve error\n", 13);
			clean_exit(mini, envp, errno);
		}
	}
	error_path(mini, envp, errno, current);
}

static void	check_special_cases(t_command *cmd, char **envp, t_mini *mini)
{
	if (!cmd->argv)
		clean_exit(mini, envp, 0);
	if (cmd->argv[0][0] == '\0')
	{
		write(STDERR_FILENO, "Command \'\' not found\n", 21);
		clean_exit(mini, envp, 127);
	}
	else if (cmd->argv[0][0] == '$' && cmd->argv[0][1] == '\0')
	{
		write(STDERR_FILENO, "$ : command not found\n", 23);
		clean_exit(mini, envp, 127);
	}
	else if (ft_strncmp("..", cmd->argv[0], ft_strlen(cmd->argv[0]) + 1) == 0)
	{
		print_executor_error("command not found", cmd->argv[0]);
		clean_exit(mini, envp, 127);
	}
	else if (ft_strncmp(".", cmd->argv[0], ft_strlen(cmd->argv[0]) + 1) == 0)
	{
		print_executor_error("filename argument required", cmd->argv[0]);
		clean_exit(mini, envp, 2);
	}
}

void	execute_cmd(t_command *cmd, char **envp, t_mini *mini)
{
	check_special_cases(cmd, envp, mini);
	if (is_builtin(cmd->argv[0]))
	{
		free_array(envp);
		envp = NULL;
		execute_builtin(mini, cmd->argv);
		clean_exit(mini, NULL, mini->exit_code);
	}
	if (cmd->argv[0][0] == '/'
			|| (cmd->argv[0][0] == '.' && cmd->argv[0][1] == '/'))
		handle_path(cmd, envp, mini);
	else
		find_path(cmd, envp, mini);
}
