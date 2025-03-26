/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_multi_strings.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:18:00 by aroullea          #+#    #+#             */
/*   Updated: 2025/03/25 10:28:27 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_no_quotes(t_bool *no_quotes, int *nb_strings)
{
	*no_quotes = TRUE;
	(*nb_strings)++;
}

static void	handle_double_quotes(t_bool *no_quotes, int *i)
{
	*no_quotes = FALSE;
	(*i)++;
}

static int	count_str(t_bool *quotes, t_bool *no_quotes)
{
	*quotes = !(*quotes);
	if (*quotes == TRUE)
	{
		*no_quotes = FALSE;
		return (0);
	}
	return (1);
}

int	is_multi_strings(char *args, int i, t_bool dquotes, t_bool squotes)
{
	int		nb_strings;
	t_bool	no_quotes;

	nb_strings = 0;
	no_quotes = FALSE;
	while (args[i] != '\0')
	{
		if ((args[i] == '\'' && !dquotes) || (args[i] == '"' && !squotes))
		{
			if (args[i] == args[i + 1] && (!dquotes && !squotes))
				handle_double_quotes(&no_quotes, &i);
			else
			{
				if (args[i] == '"')
					nb_strings += count_str(&dquotes, &no_quotes);
				else if (args[i] == '\'')
					nb_strings += count_str(&squotes, &no_quotes);
			}
		}
		else if (no_quotes == FALSE && !dquotes && !squotes)
			handle_no_quotes(&no_quotes, &nb_strings);
		i++;
	}
	return (nb_strings);
}
