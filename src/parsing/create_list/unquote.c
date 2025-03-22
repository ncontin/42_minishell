/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:39:32 by aroullea          #+#    #+#             */
/*   Updated: 2025/03/21 16:04:57 by aroullea         ###   ########.fr       */
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

static char	*handle_quotes(char *args, t_token *tokens_info, t_bool squotes)
{
	int		i;
	int		size;
	int		find;
	t_bool	dquotes;

	i = 0;
	size = 0;
	dquotes = FALSE;
	find = 0;
	while (args[i] != '\0')
	{
		if (args[i] == '\'' && !dquotes)
			squotes = !squotes;
		else if (args[i] == '"' && !squotes)
			dquotes = !dquotes;
		else
		{
			if (squotes == TRUE && args[i - 1] == '\'' && find == 0)
			{
				find++;
				tokens_info->quotes = SINGLE;
			}
			else if (dquotes == TRUE && args[i -1] == '"' && find == 0)
			{
				find++;
				tokens_info->quotes = DOUBLE;
			}
			size++;
		}
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

static t_token	*create_nodes(char **tokens)
{
	int		i;
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
	return (tokens_info);
}

t_token	*unquotes(char **tokens)
{
	int		i;
	char	*new_token;
	t_token	*tokens_info;

	i = 0;
	tokens_info = create_nodes(tokens);
	if (tokens_info == NULL)
		return (NULL);
	while (tokens[i] != NULL)
	{
		tokens_info[i].quotes = NO_QUOTES;
		new_token = handle_quotes(tokens[i], &tokens_info[i], FALSE);
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
