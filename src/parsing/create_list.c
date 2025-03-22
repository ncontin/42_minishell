/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:27:12 by aroullea          #+#    #+#             */
/*   Updated: 2025/03/22 12:43:06 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_multi_strings(char *args)
{
	int		i;
	int		nb_strings;
	t_bool	dquotes;
	t_bool	squotes;
	t_bool	no_quotes;

	i = 0;
	nb_strings = 0;
	dquotes = FALSE;
	squotes = FALSE;
	no_quotes = FALSE;
	while (args[i] != '\0')
	{
		if (args[i] == '\'' && !dquotes)
		{
			if (no_quotes == TRUE)
				no_quotes = FALSE;
			if (args[i + 1] == '\'')
				i++;
			else
			{	
				squotes = !squotes;
				if (squotes == FALSE)
					nb_strings++;
			}
		}
		else if (args[i] == '"' && !squotes)
		{
			if (no_quotes == TRUE)
				no_quotes = FALSE;
			if (args[i + 1] == '"')
				i++;
			else
			{
				dquotes = !dquotes;
				if (dquotes == FALSE)
					nb_strings++;
			}
		}
		else if (no_quotes == FALSE && !dquotes && !squotes)
		{
			no_quotes = TRUE;
			nb_strings++;
		}
		i++;
	}
	return (nb_strings);
}

void	create_list(char **tokens)
{
	int	i;
	int	nb_strings;

	i = 0;
	/*if (tokens == NULL)
		return (NULL);*/
	while (tokens[i] != NULL)
	{
		nb_strings = is_multi_strings(tokens[i]);
		i++;
	}
}
