/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_split_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:03:42 by aroullea          #+#    #+#             */
/*   Updated: 2025/03/18 11:22:36 by ncontin          ###   ########.fr       */
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
