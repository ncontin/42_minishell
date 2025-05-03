/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 05:45:58 by aroullea          #+#    #+#             */
/*   Updated: 2025/05/03 12:13:20 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	no_value(t_env *env, char *arg)
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

static int	fill_env_node(t_env *env, char *arg)
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

static t_env	*find_last(t_env *my_envp)
{
	t_env	*last;

	last = my_envp;
	while (last->next != NULL)
		last = last->next;
	return (last);
}

static void	append_env_node(t_env *envp_cp, t_env *new)
{
	t_env	*last;

	if (envp_cp == NULL)
		envp_cp = new;
	else
	{
		last = find_last(envp_cp);
		last->next = new;
	}
}

int	add_export_env(t_env *envp_cp, char *arg, t_mini *mini)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
	{
		write(STDERR_FILENO, "memory allocation failed in export\n", 34);
		return (1);
	}
	if (fill_env_node(new, arg) == 1)
	{
		mini->exit_code = 2;
		return (1);
	}
	append_env_node(envp_cp, new);
	return (0);
}
