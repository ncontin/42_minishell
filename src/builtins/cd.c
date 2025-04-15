/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:28:12 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/15 16:29:24 by ncontin          ###   ########.fr       */
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

static char	*get_env_value(t_env_node **envp_cp, char *key)
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

static void	update_old_pwd(t_env_node **env_stack, char *old_pwd)
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
			if (current->value)
			{
				free(current->value);
				current->value = NULL;
			}
			current->value = old_pwd_copy;
		}
		current = current->next;
	}
}
static char	*handle_home(t_mini *mini, char *pwd)
{
	char	*path;

	if (!mini->cmds->argv[1] || ft_strncmp(mini->cmds->argv[1], "~", 1) == 0)
	{
		path = get_env_value(mini->lst_env->envp_cp, "HOME");
		if (!path)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			free(pwd);
			return (NULL);
		}
	}
	else if (ft_strncmp(mini->cmds->argv[1], "--", (ft_strlen("--") + 1)) == 0)
	{
		mini->cmds->argv[1][0] = '.';
		mini->cmds->argv[1][1] = '.';
		path = mini->cmds->argv[1];
	}
	else
		path = mini->cmds->argv[1];
	return (path);
}

int	ft_cd(t_mini *mini)
{
	char	*pwd;
	char	*path;

	pwd = getcwd(NULL, 0);
	if (mini->cmds->argv[1] != NULL && mini->cmds->argv[2])
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		mini->exit_code = 1;
	}
	if (mini->cmds->argv[1] && !mini->cmds->argv[1][0])
		return (0);
	else if (mini->cmds->argv[1] != NULL && ft_strncmp(mini->cmds->argv[1], "-",
			(ft_strlen("-") + 1)) == 0)
	{
		ft_pwd(mini);
		free(pwd);
		return (0);
	}
	path = handle_home(mini, pwd);
	if (!path)
		return (1);
	if (chdir(path) == -1)
	{
		free(pwd);
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		perror(NULL);
		mini->exit_code = 1;
		return (mini->exit_code);
	}
	update_old_pwd(mini->lst_env->envp_cp, pwd);
	update_pwd(mini->lst_env->envp_cp);
	free(pwd);
	return (0);
}
