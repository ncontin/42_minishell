/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 05:45:58 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/30 13:43:51 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	no_value(t_env_node *env, char *arg)
{
	env->key = ft_strdup(arg);
	if (env->key == NULL)
	{
		handle_add_export_error(env, NULL);
		return (1);
	}
	env->value = NULL;
	return (0);
}

static int	fill_env_node(t_env_node *env, char *arg)
{
	int	err_code;

	err_code = 0;
	if (find_equal(arg) > 0)
	{
		env->key = get_key(arg, &err_code);
		if (err_code == 1)
		{
			handle_add_export_error(env, NULL);
			return (1);
		}
		env->value = get_value(arg, &err_code);
		if (err_code == 1)
		{
			handle_add_export_error(env, env->key);
			return (1);
		}
	}
	else
	{
		if (no_value(env, arg) == 1)
			return (1);
	}
	env->next = NULL;
	return (0);
}

static void	append_env_node(t_env *lst_env, t_env_node *env)
{
	t_env_node	*last;

	if (!(*lst_env->envp_cp))
		*lst_env->envp_cp = env;
	else
	{
		last = find_last(lst_env->envp_cp);
		last->next = env;
	}
}

int	add_export_env(t_env *lst_env, char *arg, t_mini *mini)
{
	t_env_node	*env;

	env = malloc(sizeof(t_env_node));
	if (!env)
	{
		write(STDERR_FILENO, "memory allocation failed in export\n", 34);
		return (1);
	}
	if (fill_env_node(env, arg) == 1)
	{
		mini->exit_code = 2;
		return (1);
	}
	append_env_node(lst_env, env);
	return (0);
}
