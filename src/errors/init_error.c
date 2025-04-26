/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 05:56:41 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/26 06:33:08 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_env_error(t_env_node **ft_envp, t_mini *mini)
{
	free_array(mini->lst_env->path);
	free(mini->lst_env);
	free_stack(ft_envp);
	exit (EXIT_FAILURE);
}

void	envp_to_list_error(t_mini *mini)
{
	write(STDERR_FILENO, "Memory allocation failed in envp_to_list\n", 41);
	free_array(mini->lst_env->path);
	free(mini->lst_env);
	exit(EXIT_FAILURE);
}
