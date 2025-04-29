/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:31:53 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/29 14:25:35 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_current_directory(t_mini *mini)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("cd");
		mini->exit_code = 2;
		return (NULL);
	}
	return (pwd);
}

static int	handle_cd_dash(t_mini *mini, char *pwd)
{
	if (mini->cmds->argv[1] != NULL
		&& ft_strncmp(mini->cmds->argv[1], "-", ft_strlen("-") + 1) == 0)
	{
		handle_previous_path(mini, pwd);
		return (1);
	}
	return (0);
}

static int	cd_to_path(t_mini *mini, char *path, char *pwd)
{
	if (chdir(path) == -1)
	{
		print_error_chdir(path, pwd, mini);
		return (1);
	}
	if (update_old_pwd(mini->lst_env->envp_cp) == 1
		|| update_pwd(mini->lst_env->envp_cp) == 1)
	{
		free(pwd);
		mini->exit_code = 2;
		return (1);
	}
	return (0);
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

void	ft_cd(t_mini *mini, char *path)
{
	char	*pwd;
	int		dash_result;

	pwd = get_current_directory(mini);
	if (!pwd)
		return ;
	if (handle_start_cd(mini, pwd) == 1)
		return ;
	dash_result = handle_cd_dash(mini, pwd);
	if (dash_result == 1)
		return ;
	path = handle_home(mini, pwd);
	if (!path)
		return ;
	if (cd_to_path(mini, path, pwd) == 1)
		return ;
	free(pwd);
}
