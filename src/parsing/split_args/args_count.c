/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_count.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:06:22 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/11 19:11:50 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_inquotes(t_parser *parser, int *j)
{
	int		i;
	t_bool	check_quote;
	t_bool	compare_quote;

	i = *j;
	check_quote = (parser->s[i + 1] != '"' && parser->s[i + 1] != '\'');
	compare_quote = parser->s[i] == parser->s[i + 1];
	if (compare_quote && parser->s[i + 1] == parser->quote_char)
		i++;
	else if (check_quote && parser->s[i] == parser->quote_char)
	{
		if (is_operator(parser->s + (i + 1), 0, NULL))
			parser->in_word = FALSE;
		parser->in_quotes = FALSE;
		parser->quote_char = 0;
	}
	*j = i;
}

static void	count_parse(t_parser *parser, int *j)
{
	int	i;

	i = *j;
	if (parser->in_quotes == FALSE)
	{
		if (parser->in_word == FALSE)
			parser->count++;
		parser->in_quotes = TRUE;
		parser->in_word = TRUE;
		parser->quote_char = parser->s[i];
	}
	else if (parser->s[i] == '\'' && parser->s[i + 1] == '"')
	{
		parser->quote_char = '"';
		i++;
	}
	else if (parser->s[i] == '"' && parser->s[i + 1] == '\'')
	{
		parser->quote_char = '\'';
		i++;
	}
	else
		handle_inquotes(parser, &i);
	*j = i;
}

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

int	count_args(t_parser *parser)
{
	int	i;

	i = 0;
	while (parser->s[i])
	{
		if (parser->s[i] == '"' || parser->s[i] == '\'')
			count_parse(parser, &i);
		else if ((!parser->in_quotes) && is_operator(parser->s + i, 0, NULL))
			check_operator(parser, &i);
		else if (!parser->in_word && !parser->in_quotes)
		{
			parser->in_word = TRUE;
			parser->count++;
		}
		i++;
	}
	return (parser->count);
}
