/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:39:32 by aroullea          #+#    #+#             */
/*   Updated: 2025/03/20 13:11:05 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void is_quotes(char s, t_bool *squotes, t_bool *dquotes, int *size)
{   
	int     i;

	i = 0;
	if (s == '\'' && !(*dquotes))
	{
		*squotes = !(*squotes);
		(*size)--;
	}
	if (s == '"' && !(*squotes))
	{
		*dquotes = !(*dquotes);
		(*size)--;
	}
	i++;
}

static char	*remove_quotes(char *token, int size)
{
	char	*new_token;
	int		i;
	int		j;
	t_bool	squotes;
	t_bool	dquotes;

	squotes = FALSE;
	dquotes = FALSE;
	i = 0;
	j = 0;
	new_token = (char *)malloc(sizeof(char) * (size + 1));
	if (new_token == NULL)
		return (NULL);
	while (i <= size)
	{
		if (token[i] == '\'' && !dquotes)
			squotes = !squotes;
		else if (token[i] == '"' && !squotes)
			dquotes = !dquotes;
		else
		{
			new_token[j] = token[i];
			j++;
		}
		i++;
	}
	new_token[j] = '\0';
	free(token);
	return (new_token);
}

static char *handle_quotes(char *tokens)
{
	int		i;
	int		size;
	t_bool	squotes;
	t_bool	dquotes;

	squotes = FALSE;
	dquotes = FALSE;
	i = 0;
	size = 0;
	while (tokens[i] != '\0')
	{
		is_quotes(tokens[i], &squotes, &dquotes, &size);
		i++;
		size++;
	}
	if (i != size)
		tokens = remove_quotes(tokens, size);
	return (tokens);
}

void	unquotes(char **tokens)
{
	int		i;

	i = 0;
	while (tokens[i] != NULL)
	{
		tokens[i] = handle_quotes(tokens[i]);
		i++;
	}
}
