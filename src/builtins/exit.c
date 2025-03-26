/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:03:52 by ncontin           #+#    #+#             */
/*   Updated: 2025/03/26 13:19:19 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	ft_exit(t_mini *mini)
{
	int	exit_code;

	exit_code = 0;
	if (mini->args[0] && mini->args[1])
		exit_code = ft_atoi(mini->args[1]);
	if (mini->input)
		free(mini->input);
	if (mini->args)
		free_array(mini->args);
	if (mini->lst_env)
	{
		if (mini->lst_env->envp_cp)
			free_stack(mini->lst_env->envp_cp);
		if (mini->lst_env->envp_export)
			free_stack(mini->lst_env->envp_export);
		free_path(mini->lst_env);
	}
	rl_clear_history();
	exit(exit_code);
}
