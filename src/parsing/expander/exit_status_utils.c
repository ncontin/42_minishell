/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 17:26:38 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/25 17:45:17 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_substr(char *src, int start, size_t len)
{
	char	*result;

	result = ft_substr(src, start, len);
	if (!result)
		return (NULL);
	return (result);
}

char	*handle_strjoin(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	if (!result)
		return (NULL);
	return (result);
}

void	free_three(char *a, char *b, char *c)
{
	if (a)
		free(a);
	if (b)
		free(b);
	if (c)
		free(c);
}
