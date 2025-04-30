/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:18:54 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/30 19:21:00 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_pwd(t_env_node **env_stack, t_mini *mini)
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
	if (get_or_create_pwd(current, mini, "PWD", pwd) == 1)
		return (1);
	return (0);
}

char	*get_env_value(t_env_node **envp_cp, char *key)
{
	t_env_node	*current;

	current = *envp_cp;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key)) == 0)
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

int	update_old_pwd(t_env_node **env_stack, t_mini *mini)
{
	t_env_node	*current;
	char		*old_pwd_copy;
	char		*old_pwd;

	old_pwd = get_env_value(env_stack, "PWD");
	if (!old_pwd)
		return (0);
	old_pwd_copy = ft_strdup(old_pwd);
	if (!old_pwd_copy)
	{
		write(STDERR_FILENO, "Memory allocation failed in old_pwd\n", 36);
		return (1);
	}
	current = *env_stack;
	if (get_or_create_pwd(current, mini, "OLDPWD", old_pwd_copy) == 1)
		return (1);
	return (0);
}

char	*handle_home(t_mini *mini, char *pwd)
{
	char	*path;

	if (!mini->cmds->argv[1] || ft_strncmp(mini->cmds->argv[1], "~", 1) == 0)
	{
		mini->exit_code = 0;
		path = get_env_value(mini->lst_env->envp_cp, "HOME");
		if (!path)
		{
			mini->exit_code = 1;
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			free(pwd);
			return (NULL);
		}
	}
	else
	{
		mini->exit_code = 0;
		path = mini->cmds->argv[1];
	}
	return (path);
}
