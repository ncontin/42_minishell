/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:39:32 by aroullea          #+#    #+#             */
/*   Updated: 2025/03/21 11:55:23 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*rm_quotes(char *args, int size)
{
	int		i;
	int		j;
	t_bool	squotes;
	t_bool	dquotes;

	i = 0;
	j = 0;
	squotes = FALSE;
	dquotes = FALSE;
	while (j < size)
	{
		if (args[i] == '\'' && !dquotes)
			squotes = !squotes;
		else if (args[i] == '"' && !squotes)
			dquotes = !dquotes;
		else
			args[j++] = args[i];
		i++;
	}
	args[j] = '\0';
	return (args);
}

static char	*handle_quotes(char *args, t_token *tokens_info)
{
	int		i;
	int		size;
	int		find_quotes;
	t_bool	squotes;
	t_bool	dquotes;

	squotes = FALSE;
	dquotes = FALSE;
	i = 0;
	size = 0;
	find_quotes = 0;
	while (args[i] != '\0')
	{
		if (args[i] == '\'' && !dquotes)
		{
			find_quotes++;
			if (find_quotes == 1)
				tokens_info->quotes = SINGLE;
			squotes = !squotes;
		}
		else if (args[i] == '"' && !squotes)
		{
			find_quotes++;
			if (find_quotes == 1)
				tokens_info->quotes = DOUBLE;
			dquotes = !dquotes;
		}
		else
			size++;
		i++;
	}
	if (squotes == TRUE || dquotes == TRUE)
	{
		write(2, "Error : missing closing quote\n", 30);
		return (NULL);
	}
	else if (i != size)
		args = rm_quotes(args, size);
	return (args);
}

t_token	*unquotes(char **tokens)
{
	int		i;
	char	*new_token;
	t_token	*tokens_info;

	i = 0;
	while (tokens[i] != NULL)
		i++;
	tokens_info = (t_token *)malloc(sizeof(t_token) * i);
	if (tokens_info == NULL)
	{
		free_array(tokens);
		return (NULL);
	}
	i = 0;
	while (tokens[i] != NULL)
	{
		tokens_info[i].quotes = NO_QUOTES;
		new_token = handle_quotes(tokens[i], &tokens_info[i]);
		if (new_token == NULL)
		{
			free_array(tokens);
			return (NULL);
		}
		tokens_info[i].argument = new_token;
		tokens[i] = new_token;
		i++;
	}
	return (tokens_info);
}
