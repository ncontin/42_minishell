/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_wordlen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:35:44 by aroullea          #+#    #+#             */
/*   Updated: 2025/03/18 15:18:11 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	no_quotes(char const *s, t_bool *dquotes, t_bool *squotes, int *len)
{
	int	size;

	size = *len;
	if (s[size] == '"')
		*dquotes = TRUE;
	else if (s[size] == '\'')
		*squotes = TRUE;
	size++;
	while ((s[size] == '"' || s[size] == '\'') && s[size] == s[size + 1])
	{
		if (s[size] == '"' && !squotes)
			*dquotes = !(*dquotes);
		else if (s[size] == '\'' && !dquotes)
			*squotes = !(*squotes);
		size++;
	}
	*len = size;
}

static void	in_quotes(char const *s, t_bool *dquotes, t_bool *squotes, int *len)
{
	int		next;
	int		size;

	size = *len;
	next = size + 1;
	if ((s[next] == '"' && *dquotes) || (s[next] == '\'' && *squotes))
		size += 2;
	else
	{
		if (s[size] == '"')
		{
			*dquotes = FALSE;
			size++;
		}
		else if (s[size] == '\'')
		{
			*squotes = FALSE;
			size++;
		}
	}
	*len = size;
}

int	wordlen(char const *s, t_bool dquotes, t_bool squotes)
{
	int		len;

	len = 0;
	while (s[len])
	{
		if ((s[len] == '"' && dquotes) || (s[len] == '\'' && squotes))
			in_quotes(s, &dquotes, &squotes, &len);
		else if ((s[len] == '"' && !squotes) || (s[len] == '\'' && !dquotes))
			no_quotes(s, &dquotes, &squotes, &len);
		else if (!dquotes && !squotes && is_operator(s + len, 0, NULL))
		{
			if (len == 0)
			{
				is_operator(s + len, 0, &len);
				len++;
			}
			break ;
		}
		else
			len++;
	}
	return (len);
}
