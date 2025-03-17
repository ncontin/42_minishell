/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_split_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:03:42 by aroullea          #+#    #+#             */
/*   Updated: 2025/03/16 13:19:15 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_operator(char const *c, int no_space, int *len)
{
	if ((c[0] == '>' && c[1] == '>') || (c[0] == '<' && c[1] == '<'))
		(*len)++;
	if ((c[0] == '>') || (c[0] == '<') || (c[0] == '|'))
		return (TRUE);
	if ((no_space == 0) && (c[0] == ' '))
		return (TRUE);
	return (FALSE);
}

void	add_len(char const *s, t_bool *dquotes, int *len)
{
	if (dquotes == FALSE && s[(*len) + 1] != '"')
		(*len)++;
}
