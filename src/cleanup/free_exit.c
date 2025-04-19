/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:11:35 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/08 12:21:26 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_exit(t_mini *mini)
{
	if (mini->input)
		free(mini->input);
	if (mini->cmds)
	{
		free_commands(mini->cmds);
		mini->cmds = NULL;
	}
	if (mini->lst_env)
	{
		if (mini->lst_env->envp_cp)
			free_stack(mini->lst_env->envp_cp);
		free_path(mini->lst_env);
		free(mini->lst_env);
		mini->lst_env = NULL;
	}
}

void	clean_exit(t_mini *mini, char **envp, int exit_code)
{
    free_array(envp);
    free_exit(mini);
    exit(exit_code);
}
