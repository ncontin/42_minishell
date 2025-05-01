/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   previous_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:17:44 by aroullea          #+#    #+#             */
/*   Updated: 2025/05/01 05:50:51 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_valid_oldpwd(t_mini *mini, char *pwd)
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
	if (check_cd_path(path) == 1)
	{
		free(pwd);
		mini->exit_code = 1;
		return (NULL);
	}
	return (path);
}

static void	change_directory_and_update_env(t_mini *mini, char *pwd, char *path)
{
	if (chdir(path) == -1)
	{
		print_error_chdir(path, pwd, mini);
		return ;
	}
	mini->exit_code = 0;
	if (update_old_pwd(mini->lst_env->envp_cp, mini) == 1)
	{
		free(pwd);
		mini->exit_code = 2;
		return ;
	}
	if (update_pwd(mini->lst_env->envp_cp, mini) == 1)
	{
		free(pwd);
		mini->exit_code = 2;
		return ;
	}
	free(pwd);
	ft_pwd(mini);
}

void	handle_previous_path(t_mini *mini, char *pwd)
{
	char	*path;

	path = get_valid_oldpwd(mini, pwd);
	if (path == NULL)
		return ;
	change_directory_and_update_env(mini, pwd, path);
}
