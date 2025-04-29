/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joined_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 06:56:48 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/29 09:41:10 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	allocate_temp_and_str(t_env_node *env_to_replace, char *arg,
		char **temp, char **str_to_join)
{
	int	err_code;

	err_code = 0;
	*str_to_join = get_value(arg, &err_code);
	if (err_code == 1)
	{
		write(STDERR_FILENO, "memory allocation failed in export\n", 34);
		return (1);
	}
	*temp = ft_strdup(env_to_replace->value);
	if (*temp == NULL)
	{
		handle_join_env_error(*str_to_join, NULL);
		return (1);
	}
	return (0);
}

int	join_env_value(t_env_node *env_to_replace, char *arg, t_mini *mini)
{
	char	*temp;
	char	*str_to_join;
	char	*tmp_value;

	if (allocate_temp_and_str(env_to_replace, arg, &temp, &str_to_join))
	{
		mini->exit_code = 2;
		return (1);
	}
	tmp_value = ft_strjoin(temp, str_to_join);
	if (tmp_value == NULL)
	{
		mini->exit_code = 2;
		handle_join_env_error(str_to_join, temp);
		return (1);
	}
	free(env_to_replace->value);
	env_to_replace->value = tmp_value;
	free(temp);
	free(str_to_join);
	return (0);
}
