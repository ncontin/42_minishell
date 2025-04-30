/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 09:43:19 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/30 13:43:40 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_envp_error(t_mini *mini)
{
	mini->exit_code = 2;
	write(STDERR_FILENO, "memory allocation failed in export\n", 35);
}

void	copy_env_node_error(t_env_node **ft_envp, t_mini *mini)
{
	mini->exit_code = 2;
	write(STDERR_FILENO, "Memory allocation failed in copy_env\n", 37);
	if (ft_envp != NULL)
		free_stack(ft_envp);
}

void	handle_join_env_error(char *str1, char *str2)
{
	write(STDERR_FILENO, "memory allocation failed in export\n", 35);
	if (str1)
		free(str1);
	if (str2)
		free(str2);
}

void	print_id_error(t_mini *mini, char *arg)
{
	mini->exit_code = 1;
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

void	handle_add_export_error(t_env_node *env, char *key)
{
	write(STDERR_FILENO, "memory allocation failed in export\n", 35);
	if (key)
		free(key);
	if (env)
		free(env);
}
