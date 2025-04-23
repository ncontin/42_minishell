/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_count.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:06:22 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/23 04:22:12 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_operator(t_parser *parser, int *j)
{
	int	i;

	i = *j;
	if (parser->in_word)
	{
		parser->in_word = FALSE;
		if ((ft_isspace(parser->s[i]) == 0)
			&& is_operator(parser->s + i, 0, &i))
			parser->count++;
	}
	else if (is_operator(parser->s + i, 1, &i))
		parser->count++;
	*j = i;
}

static void	handle_quote_state(t_parser *parser, char c)
{
	if (!parser->in_quotes)
	{
		parser->in_quotes = TRUE;
		parser->quote_char = c;
	}
	else if (parser->quote_char == c)
	{
		parser->in_quotes = FALSE;
		parser->quote_char = 0;
	}
}

int	count_args(t_parser *parser, int i)
{
	while (parser->s[i])
	{
		if (parser->s[i] == '"' || parser->s[i] == '\'')
		{
			handle_quote_state(parser, parser->s[i]);
			if (!parser->in_word)
			{
				parser->in_word = TRUE;
				parser->count++;
			}
		}
		else if (!parser->in_quotes && is_operator(parser->s + i, 0, NULL))
			check_operator(parser, &i);
		else if (!parser->in_word && !ft_isspace(parser->s[i]))
		{
			parser->in_word = TRUE;
			parser->count++;
		}
		else if (ft_isspace(parser->s[i]) && !parser->in_quotes)
			parser->in_word = FALSE;
		i++;
	}
	return (parser->count);
}
