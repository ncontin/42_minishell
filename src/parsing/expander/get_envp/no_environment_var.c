/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_environment_var.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 09:23:57 by aroullea          #+#    #+#             */
/*   Updated: 2025/05/03 09:27:08 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_parts(char *full_str, int i, char **before, char **after)
{
	size_t	len;
	size_t	size;

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

char	*no_args(char *full_str, int i, int *err_code)
{
	char	*before;
	char	*after;
	char	*temp;

	if (get_parts(full_str, i, &before, &after) == 1)
	{
		free(full_str);
		*err_code = 1;
		return (NULL);
	}
	temp = handle_strjoin(before, after);
	if (temp == NULL)
	{
		free_three(before, after, full_str);
		*err_code = 1;
		return (NULL);
	}
	free_three(before, after, full_str);
	return (temp);
}
