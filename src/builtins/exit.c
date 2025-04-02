/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:03:52 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/02 16:15:09 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_mini *mini)
{
	int	exit_code;

	exit_code = 0;
	if (mini->cmds->argv[0] && mini->cmds->argv[1])
		exit_code = ft_atoi(mini->cmds->argv[1]);
	if (mini->input)
		free(mini->input);
	if (mini->args)
		free_array(mini->args);
	if (mini->tokens)
		free_token(mini->tokens);
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
