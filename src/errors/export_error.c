/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 09:43:19 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/29 05:37:11 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_envp_error(t_mini *mini)
{
	mini->exit_code = 1;
	write(STDERR_FILENO, "memory allocation failed in export\n", 35);
}

void	copy_env_node_error(t_env_node **ft_envp, t_mini *mini)
{
	mini->exit_code = 1;
	write(STDERR_FILENO, "Memory allocation failed in copy_env\n", 37);
	if (ft_envp != NULL)
		free_stack(ft_envp);
}

int	handle_join_env_error(char *str1, char *str2)
{
	write(STDERR_FILENO, "memory allocation failed in export\n", 34);
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	return (1);
}
