/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_split_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:03:42 by aroullea          #+#    #+#             */
/*   Updated: 2025/03/19 11:49:47 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_operator(char const *c, int no_space, int *len)
{
	if (len != NULL)
	{
		if ((c[0] == '>' && c[1] == '>') || (c[0] == '<' && c[1] == '<'))
			(*len)++;
		else if ((c[0] == '&' && c[1] == '&') || (c[0] == '|' && c[1] == '|'))
			(*len)++;
	}
	if ((c[0] == '(') || (c[0] == ')') || c[0] == '&')
		return (TRUE);
	else if ((c[0] == '>') || (c[0] == '<') || (c[0] == '|'))
		return (TRUE);
	if ((no_space == 0) && (c[0] == ' '))
		return (TRUE);
	return (FALSE);
}

char	*shell_join(char *s1, char const *s2, size_t k, size_t l)
{
	size_t	i;
	char	*str;

	i = 0;
	str = malloc(sizeof(char) * (k + l + 1));
	if (str == NULL)
	{
		free(s1);
		return (NULL);
	}
	while (i < k)
	{
		str[i] = s1[i];
		i++;
	}
	while (i < k + l)
	{
		str[i] = s2[i - k];
		i++;
	}
	str[k + l] = '\0';
	free(s1);
	return (str);
}
