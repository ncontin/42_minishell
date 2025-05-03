/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:38:46 by ncontin           #+#    #+#             */
/*   Updated: 2025/05/03 09:47:35 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_mini *mini, char **cmd_args)
{
	if (cmd_args[1] != NULL)
	{
		ft_putstr_fd("env: ’", STDERR_FILENO);
		ft_putstr_fd(mini->cmds->argv[1], STDERR_FILENO);
		ft_putstr_fd("’: No such file or directory\n", STDERR_FILENO);
		mini->exit_code = 127;
		return ;
	}
	else
	{
		print_env(mini->envp_cp);
		mini->exit_code = 0;
	}
}
