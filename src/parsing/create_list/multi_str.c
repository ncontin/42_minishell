/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 14:42:26 by aroullea          #+#    #+#             */
/*   Updated: 2025/03/23 18:16:45 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_str(char *args, int *size, t_token *current)
{
	int		i;
	t_bool	in_str;
	char	quote_char;

	i = 0;
	in_str = FALSE;
	*size = 0;
	quote_char = '\0';
	while (args[i] != '\0')
	{
		if (args[i] == '\'' && (in_str == FALSE))
		{
			if (args[i + 1] == '\'')
				i++;
			else
			{
				in_str = TRUE;
				quote_char = '\'';
				current->quotes = SINGLE;
			}
		}
		else if (args[i] == '"' && (in_str == FALSE))
		{
			if (args[i + 1] == '"')
				i++;
			else
			{
				in_str = TRUE;
				quote_char = '"';
				current->quotes = DOUBLE;
			}
		}
		else
		{
			if (args[i] == quote_char)
			{
				i++;
				break ;
			}
			if (current->quotes == NO_QUOTES && (args[i] == '"' || args[i] == '\''))
				break ;
			in_str = TRUE;
			(*size)++;
		}
		i++;
	}
	return (args + i);
}

void	multi_str(char *args, int nb_strings, t_token **head)
{
	int		i;
	int		size;
	char	*next_str;
	char	*string;
	t_token	*current;

	i = 0;
	size = 0;
	string = args;
	while (i < nb_strings)
	{
		current = init_new_list(*head);
		if (current == NULL)
			return ;
		next_str = get_str(string, &size, current);
		current->argument = rm_quotes(string, size);
		if (current->argument == NULL)
		{
			write(2, "Memory allocation failed to create arg\n", 39);
			free_token(*head);
			return ;
		}
		string = next_str;
		lst_add_new(head, current);
		i++;
		if (i != nb_strings)
			current->linked = TRUE;
	}
}
