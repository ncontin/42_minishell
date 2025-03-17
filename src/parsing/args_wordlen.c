/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wordlen_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:35:44 by aroullea          #+#    #+#             */
/*   Updated: 2025/03/17 17:43:47 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	no_quotes(char const *s, t_bool *dquotes, t_bool *squotes, int *len)
{
	int	lenght;

	lenght = *len;
	if (s[lenght] == '"')
		*dquotes = TRUE;
	else if (s[lenght] == '\'')
		*squotes = TRUE;
	lenght++;
	while (s[lenght] == '"' || s[lenght] == '\'')
	{
		if (s[lenght] == '"')
			*dquotes = !(*dquotes);
		else if (s[lenght] == '\'')
			*squotes = !(*squotes);
		lenght++;
	}
	*len = lenght;
}

static void	in_quotes(char const *s, t_bool *dquotes, t_bool *squotes, int *len)
{
	int		next;
	int		lenght;

	lenght = *len;
	next = lenght + 1;
	if ((s[next] == '"' && *dquotes) || (s[next] == '\'' && *squotes))
		lenght += 2;
	else
	{
		if (s[lenght] == '"')
			*dquotes = FALSE;
		else if (s[lenght] == '\'')
			*squotes = FALSE;
		lenght++;
	}
	*len = lenght;
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
