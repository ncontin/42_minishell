/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 07:20:09 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/29 07:25:35 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	replace_key_value(t_env_node *env_to_replace, char *arg)
{
	t_env_node	tmp;
	int			err_code;

	err_code = 0;
	tmp.key = get_key(arg, &err_code);
	if (err_code == 1)
		return (1);
	tmp.value = get_value(arg, &err_code);
	if (err_code == 1)
	{
		free(tmp.key);
		return (1);
	}
	free(env_to_replace->key);
	free(env_to_replace->value);
	env_to_replace->key = tmp.key;
	env_to_replace->value = tmp.value;
	return (0);
}

static int	replace_key_only(t_env_node *env_to_replace, char *arg)
{
	char	*key;

	key = ft_strdup(arg);
	if (!key)
	{
		write(STDERR_FILENO, "memory allocation failed in export\n", 34);
		return (1);
	}
	free(env_to_replace->key);
	free(env_to_replace->value);
	env_to_replace->key = key;
	env_to_replace->value = NULL;
	return (0);
}

int	replace_env(t_env_node *env_to_replace, char *arg)
{
	int	equal_index;

	equal_index = find_equal(arg);
	if (equal_index > 0)
	{
		if (replace_key_value(env_to_replace, arg) == 1)
			return (1);
		return (0);
	}
	else
	{
		if (replace_key_only(env_to_replace, arg) == 1)
			return (1);
		return (0);
	}
}
