/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:12:56 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/30 19:19:55 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_no_exec(t_command *current, char **envp, t_mini *mini, int error)
{
	if (error == ENOENT)
	{
		print_executor_error("command not found", current->argv[0]);
		clean_exit(mini, envp, 127);
	}
	else if (error == EACCES)
	{
		print_executor_error("Permission denied", current->argv[0]);
		clean_exit(mini, envp, 126);
	}
	else if (error == ENOEXEC)
	{
		print_executor_error("Exec format error", current->argv[0]);
		clean_exit(mini, envp, 126);
	}
}

int	is_user_in_bin(t_mini *mini, t_command *cmd, char **envp)
{
	char	*path;
	char	*bin_folder;

	bin_folder = getcwd(NULL, 0);
	if (bin_folder == NULL)
	{
		write(STDERR_FILENO, "Memory allocation failed", 24);
		write(STDERR_FILENO, "in user_in_bin\n", 14);
		clean_exit(mini, envp, 2);
	}
	if (ft_strncmp(bin_folder, "/usr/bin", 8) == 0)
	{
		path = copy_command(bin_folder, cmd->argv[0]);
		if (execve(path, cmd->argv, envp) == -1)
		{
			write(STDERR_FILENO, "execve error\n", 13);
			free(bin_folder);
			free(path);
			clean_exit(mini, envp, 1);
		}
	}
	return (0);
}

void	is_path_a_directory(t_command *current, char **envp, t_mini *mini)
{
	struct stat	statbuf;

	if (lstat(current->argv[0], &statbuf) == 0)
	{
		if (S_ISDIR(statbuf.st_mode))
		{
			print_executor_error("Is a directory", current->argv[0]);
			clean_exit(mini, envp, 126);
		}
	}
	else
	{
		perror("lstat");
		clean_exit(mini, envp, 1);
	}
}

void	update_underscore_path(char *path, t_env_node **envp_cp, t_mini *mini)
{
	t_env_node	*current;

	current = *envp_cp;
	while (current != NULL)
	{
		if (ft_strncmp(current->key, "_", ft_strlen(current->key) + 1) == 0)
		{
			free(current->value);
			current->value = path;
			return ;
		}
		if (current->next == NULL)
		{
			if (add_export_env(mini->lst_env, "_", mini) == 1)
				return ;
		}
		current = current->next;
	}
}

void	free_and_exit(t_mini *mini, char **unix_path, char **envp)
{
	if (unix_path != NULL)
		free_array(unix_path);
	clean_exit(mini, envp, 1);
}
