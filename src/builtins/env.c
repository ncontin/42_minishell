/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:38:46 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/14 16:43:40 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_mini *mini)
{
	if (mini->cmds->argv[1] != NULL)
	{
		ft_putstr_fd("env: ’", 2);
		ft_putstr_fd(mini->cmds->argv[1], 2);
		ft_putstr_fd("’: No such file or directory\n", 2);
		return ;
	}
	else
		print_env(mini->lst_env->envp_cp);
}
