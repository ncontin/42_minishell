/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:18:54 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/24 12:12:55 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_pwd(t_env_node **env_stack)
{
	char		*pwd;
	t_env_node	*current;

	pwd = getcwd(NULL, 0);
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

static void	add_old_pwd(t_env_node *last, char *old_pwd)
{
	t_env_node	*new;

	new = (t_env_node *)malloc(sizeof(t_env_node));
	if (new == NULL)
		return ;
	new->key = ft_strdup("OLDPWD");
	if (new->key == NULL)
	{
		free(new);
		return ;
	}
	new->value = old_pwd;
	new->next = NULL;
	last->next = new;
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

void	update_old_pwd(t_env_node **env_stack, char *old_pwd)
{
	t_env_node	*current;
	char		*old_pwd_copy;

	if (old_pwd == NULL)
	{
		old_pwd = get_env_value(env_stack, "PWD");
		if (old_pwd == NULL)
			return ;
	}
	old_pwd_copy = ft_strdup(old_pwd);
	if (!old_pwd_copy)
		return ;
	current = *env_stack;
	while (current)
	{
		if (strncmp(current->key, "OLDPWD", 6) == 0)
		{
			free(current->value);
			current->value = old_pwd_copy;
			return ;
		}
		if (current->next == NULL)
		{
			add_old_pwd(current, old_pwd_copy);
			break ;
		}
		current = current->next;
	}
}
