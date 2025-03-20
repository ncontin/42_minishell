/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:39:32 by aroullea          #+#    #+#             */
/*   Updated: 2025/03/20 17:27:23 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	is_quotes(char s, t_bool *squotes, t_bool *dquotes, int *size)
{
	int	i;

	i = 0;
	if (s == '\'' && !(*dquotes))
	{
		*squotes = !(*squotes);
		(*size)--;
	}
	else if (s == '"' && !(*squotes))
	{
		*dquotes = !(*dquotes);
		(*size)--;
	}
	i++;
}

static char	*rm_quotes(char *args, int size, t_bool squotes, t_bool dquotes)
{
	char	*new_token;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_token = (char *)malloc(sizeof(char) * (size + 1));
	if (new_token == NULL)
		return (NULL);
	while (j < size)
	{
		if (args[i] == '\'' && !dquotes)
			squotes = !squotes;
		else if (args[i] == '"' && !squotes)
			dquotes = !dquotes;
		else
		{
			new_token[j] = args[i];
			j++;
		}
		i++;
	}
	new_token[j] = '\0';
	free(args);
	return (new_token);
}

static char	*handle_quotes(char *args)
{
	int		i;
	int		size;
	t_bool	squotes;
	t_bool	dquotes;

	squotes = FALSE;
	dquotes = FALSE;
	i = 0;
	size = 0;
	while (args[i] != '\0')
	{
		is_quotes(args[i], &squotes, &dquotes, &size);
		i++;
		size++;
	}
	if (squotes == TRUE || dquotes == TRUE)
	{
		write(2, "Error : missing closing quote\n", 30);
		free(args);
		return (NULL);
	}
	else if (i != size)
		args = rm_quotes(args, size, FALSE, FALSE);
	return (args);
}

char	**unquotes(char **tokens)
{
	int		i;

	i = 0;
	while (tokens[i] != NULL)
	{
		tokens[i] = handle_quotes(tokens[i]);
		if (tokens[i] == NULL)
		{
			free_array(tokens);
			tokens = NULL;
			break ;
		}
		i++;
	}
	return (tokens);
}
