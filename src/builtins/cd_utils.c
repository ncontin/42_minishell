/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:18:54 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/29 11:56:49 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_pwd(t_env_node **env_stack)
{
	char		*pwd;
	t_env_node	*current;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		write(STDERR_FILENO, "Memory allocation failed", 24);
		write(STDERR_FILENO, "to update pwd\n", 14);
		return (1);
	}
	current = *env_stack;
	while (current)
	{
		if (strncmp(current->key, "PWD", 3) == 0)
		{
			free(current->value);
			current->value = pwd;
		}
		current = current->next;
	}
	return (0);
}

char	*get_env_value(t_env_node **envp_cp, char *key)
{
	t_env_node	*current;

	current = *envp_cp;
	while (current)
	{
		if (strncmp(current->key, key, strlen(key)) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

int	check_cd_path(char *path)
{
	struct stat	statbuf;

	if (access(path, F_OK) != 0)
	{
		print_error_cd("No such file or directory", path);
		return (1);
	}
	if (access(path, X_OK) != 0)
	{
		print_error_cd("Permission denied", path);
		return (1);
	}
	if (stat(path, &statbuf) != 0)
	{
		write(STDERR_FILENO, "cd: stat error\n", 16);
		return (1);
	}
	if (!S_ISDIR(statbuf.st_mode))
	{
		print_error_cd("Not a directory", path);
		return (1);
	}
	return (0);
}

int	update_old_pwd(t_env_node **env_stack)
{
	t_env_node	*current;
	char		*old_pwd_copy;
	char		*old_pwd;

	old_pwd = get_env_value(env_stack, "PWD");
	if (!old_pwd)
		return (1);
	old_pwd_copy = ft_strdup(old_pwd);
	if (!old_pwd_copy)
	{
		write(STDERR_FILENO, "Memory allocation failed", 24);
		write(STDERR_FILENO, "to update old_pwd\n", 18);
		return (1);
	}
	current = *env_stack;
	while (current)
	{
		if (strncmp(current->key, "OLDPWD", 6) == 0)
		{
			free(current->value);
			current->value = old_pwd_copy;
			return (0);
		}
		current = current->next;
	}
	return (0);
}
