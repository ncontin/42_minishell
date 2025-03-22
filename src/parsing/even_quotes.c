/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   even_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 10:31:00 by aroullea          #+#    #+#             */
/*   Updated: 2025/03/22 12:27:08 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	handle_quotes(char *args)
{
	int		i;
	t_bool	dquotes;
	t_bool	squotes;

	dquotes = FALSE;
	squotes = FALSE;
	i = 0;
	while (args[i] != '\0')
	{
		if (args[i] == '\'' && !dquotes)
			squotes = !squotes;
		else if (args[i] == '"' && !squotes)
			dquotes = !dquotes;
		i++;
	}
	if (squotes == TRUE || dquotes == TRUE)
	{
		write(2, "Error : missing closing quote\n", 30);
		return (FALSE);
	}
	return (TRUE);
}

t_bool	is_even_quotes(char **tokens)
{
	t_bool	even_quotes;
	int		i;

	i = 0;
	while (tokens[i] != NULL)
	{
		even_quotes = handle_quotes(tokens[i]);
		if (even_quotes == FALSE)
		{
			free_array(tokens);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}
