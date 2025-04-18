/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_multi_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 14:42:26 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/18 14:51:32 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	str_found(char c, char *quote, int *i, t_token *current)
{
	if (c == *quote)
	{
		(*i)++;
		return (1);
	}
	if (current->quotes == NO_QUOTES && (c == '"' || c == '\''))
		return (1);
	return (0);
}

static void	in_quotes(char c, t_bool *in_str, char *quote, t_token *current)
{
	*in_str = TRUE;
	*quote = c;
	if (c == '\'')
		current->quotes = SINGLE;
	else if (c == '"')
		current->quotes = DOUBLE;
}

static char	*get_str(char *args, int *size, t_token *current, char quote_char)
{
	int		i;
	t_bool	in_str;

	i = 0;
	in_str = FALSE;
	*size = 0;
	while (args[i] != '\0')
	{
		if ((args[i] == '\'' || args[i] == '"') && (in_str == FALSE))
		{
			if (args[i] == args[i + 1])
				i++;
			else
				in_quotes(args[i], &in_str, &quote_char, current);
		}
		else
		{
			if (str_found(args[i], &quote_char, &i, current) == 1)
				break ;
			in_str = TRUE;
			(*size)++;
		}
		i++;
	}
	return (args + i);
}

void	multi_str(char *args, int nb_strings, t_token **head, int i)
{
	int		size;
	char	*next_str;
	char	*string;
	t_token	*current;

	size = 0;
	string = args;
	while (i < nb_strings)
	{
		current = init_new_list(*head);
		if (current == NULL)
			return ;
		next_str = get_str(string, &size, current, '\0');
		current->argument = rm_quotes(string, size);
		if (current->argument == NULL)
		{
			error_create_list(*head, current);
			return ;
		}
		string = next_str;
		lst_add_new(head, current);
		i++;
		if (i != nb_strings)
			current->linked = TRUE;
	}
}
