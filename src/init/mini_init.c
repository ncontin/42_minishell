/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:08:41 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/08 12:22:46 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_mini(t_mini *mini)
{
	mini->args = NULL;
	mini->exit_code = 0;
	mini->lst_env = malloc(sizeof(t_env));
	if (!mini->lst_env)
		return ;
	mini->tokens = NULL;
	mini->cmds = NULL;
	mini->error = 0;
}
