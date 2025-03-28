/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:38:46 by ncontin           #+#    #+#             */
/*   Updated: 2025/03/28 16:17:59 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_mini *mini)
{
	print_env_stack(mini->lst_env->envp_cp);
	if (mini->lst_env->envp_export)
		print_env_stack(mini->lst_env->envp_export);
}
