/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 09:43:19 by aroullea          #+#    #+#             */
/*   Updated: 2025/05/03 11:28:36 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_envp_error(t_mini *mini)
{
	mini->exit_code = 2;
	write(STDERR_FILENO, "memory allocation failed in export\n", 35);
}

void	copy_env_node_error(t_env *sorted_envp_cp, t_mini *mini)
{
	mini->exit_code = 2;
	write(STDERR_FILENO, "Memory allocation failed in copy_env\n", 37);
	if (sorted_envp_cp != NULL)
		free_stack(sorted_envp_cp);
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

void	handle_add_export_error(t_env *env, char *key)
{
	write(STDERR_FILENO, "memory allocation failed in export\n", 35);
	if (key)
		free(key);
	if (env)
		free(env);
}
