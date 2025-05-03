/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_environment_var.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 10:18:02 by aroullea          #+#    #+#             */
/*   Updated: 2025/05/03 09:36:25 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_parts(char *full_str, int i, char **before, char **after)
{
	size_t		len;
	size_t		size;

	len = find_word_len(&full_str[i + 1], i);
	*before = handle_substr(full_str, 0, i);
	if (*before == NULL)
		return (1);
	size = ft_strlen(full_str) - i - len - 1;
	*after = handle_substr(full_str, i + len + 1, size);
	if (*after == NULL)
	{
		free(*before);
		*before = NULL;
		return (1);
	}
	return (0);
}

static char	*build_env_var(char *before, char *after, t_env *current,
		int *err_code)
{
	char	*result;
	char	*tmp;

	result = get_current_value(current->value);
	tmp = handle_strjoin(before, result);
	if (tmp == NULL)
	{
		*err_code = 1;
		return (NULL);
	}
	result = handle_strjoin(tmp, after);
	free(tmp);
	if (result == NULL)
		*err_code = 1;
	return (result);
}

char	*get_env_var(char *full_str, t_env *current, int i, int *err_code)
{
	char	*before;
	char	*after;
	char	*result;

	if (get_parts(full_str, i, &before, &after) == 1)
	{
		free(full_str);
		*err_code = 1;
		return (NULL);
	}
	result = build_env_var(before, after, current, err_code);
	free_three(full_str, before, after);
	return (result);
}
