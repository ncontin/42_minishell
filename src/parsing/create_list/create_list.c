/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:27:12 by aroullea          #+#    #+#             */
/*   Updated: 2025/03/23 10:07:01 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	str_count(char *args, t_bool *quotes, int *i, char c)
{
	if (args[*i + 1] == c)
		(*i)++;
	else
	{
		*quotes = !(*quotes);
		if (*quotes == FALSE)
			return (1);
	}
	return (0);
}

static int	is_multi_strings(char *args, int i, t_bool dquotes, t_bool squotes)
{
	int		nb_strings;
	t_bool	no_quotes;

	nb_strings = 0;
	no_quotes = FALSE;
	while (args[i] != '\0')
	{
		if (args[i] == '\'' && !dquotes)
		{
			no_quotes = FALSE;
			nb_strings += str_count(args, &squotes, &i, '\'');
		}
		else if (args[i] == '"' && !squotes)
		{
			no_quotes = FALSE;
			nb_strings += str_count(args, &dquotes, &i, '"');
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

static t_token	*new_list(char *args, int nb_strings)
{
	t_token	*current;
	int		size;

	if (nb_strings == 1)
	{
		current = (t_token *)malloc(sizeof(t_token));
		if (current == NULL)
		{
			free_token(current);
			return (NULL);
		}
		check_quotes(args, current);
		size = get_size(args);
		current->argument = rm_quotes(args, size);
	}
	/*else
	  handle_multi_str();*/
	return (current);
}

void	create_list(char **tokens)
{
	int		i;
	int		nb_strings;

	i = 0;
	while (tokens[i] != NULL)
	{
		nb_strings = is_multi_strings(tokens[i], 0, FALSE, FALSE);
		new_list(tokens[i], nb_strings);
		i++;
	}
}
