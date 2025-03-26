/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:38:46 by ncontin           #+#    #+#             */
/*   Updated: 2025/03/24 11:53:20 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_env *lst_env)
{
	print_env_stack(lst_env->envp_cp);
	if (lst_env->envp_export)
		print_env_stack(lst_env->envp_export);
}
