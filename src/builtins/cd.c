/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:28:12 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/24 18:09:17 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_previous_path(t_mini *mini, char *pwd)
{
	char	*path;

	path = get_env_value(mini->lst_env->envp_cp, "OLDPWD");
	if (!path)
	{
		free(pwd);
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		mini->exit_code = 1;
		return (NULL);
	}
	else if (check_cd_path(path))
	{
		free(pwd);
		mini->exit_code = 1;
		return (NULL);
	}
	if (chdir(path) == -1)
		print_error_chdir(path, pwd, mini);
	else
	{
		mini->exit_code = 0;
		update_old_pwd(mini->lst_env->envp_cp, pwd);
		update_pwd(mini->lst_env->envp_cp);
		free(pwd);
		ft_pwd(mini);
	}
	return (path);
}

static char	*handle_home(t_mini *mini, char *pwd)
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
		path = mini->cmds->argv[1];
		mini->exit_code = 0;
	}
	return (path);
}

static int	handle_start_cd(t_mini *mini, char *pwd)
{
	if (mini->cmds->argv[1] != NULL && mini->cmds->argv[2])
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		mini->exit_code = 1;
		free(pwd);
		return (1);
	}
	if (mini->cmds->argv[1] && !mini->cmds->argv[1][0])
	{
		free(pwd);
		return (1);
	}
	return (0);
}

int	ft_cd(t_mini *mini, char *path)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (handle_start_cd(mini, pwd) == 1)
		return (0);
	if (mini->cmds->argv[1] != NULL
			&& ft_strncmp(mini->cmds->argv[1], "-", (ft_strlen("-") + 1)) == 0)
	{
		path = handle_previous_path(mini, pwd);
		if (!path)
			return (1);
		return (mini->exit_code);
	}
	path = handle_home(mini, pwd);
	if (!path)
		return (1);
	if (chdir(path) == -1)
	{
		print_error_chdir(path, pwd, mini);
		return (mini->exit_code);
	}
	update_old_pwd(mini->lst_env->envp_cp, pwd);
	update_pwd(mini->lst_env->envp_cp);
	free(pwd);
	return (0);
}
