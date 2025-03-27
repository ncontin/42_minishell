/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:28:12 by ncontin           #+#    #+#             */
/*   Updated: 2025/03/27 08:58:06 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_pwd(t_env_node **env_stack)
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

static void	update_old_pwd(t_env_node **env_stack, char *old_pwd)
{
	t_env_node	*current;

	current = *env_stack;
	while (current)
	{
		if (strncmp(current->key, "OLDPWD", 6) == 0)
		{
			free(current->value);
			current->value = old_pwd;
		}
		current = current->next;
	}
}

int	ft_cd(char *path, t_env *env_lst)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!path)
		return (1);
	if (chdir(path) == -1)
	{
		perror("cd");
		return (1);
	}
	else
	{
		update_old_pwd(env_lst->envp_cp, pwd);
		update_pwd(env_lst->envp_cp);
	}
	return (0);
}
