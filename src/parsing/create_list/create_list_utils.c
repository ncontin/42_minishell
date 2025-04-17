/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:24:52 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/17 11:32:16 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_quotes	get_quote_type(char *args, char c, t_bool *quote, int *i)
{
	if (args[*i + 1] == c)
		(*i)++;
	else
	{
		*quote = !(*quote);
		if (c == '\'')
			return (SINGLE);
		else if (c == '"')
			return (DOUBLE);
	}
	return (NO_QUOTES);
}

void	check_quotes(char *args, t_token *current)
{
	int		i;
	t_bool	dquotes;
	t_bool	squotes;

	i = 0;
	squotes = FALSE;
	dquotes = FALSE;
	current->quotes = NO_QUOTES;
	while (args[i] != '\0')
	{
		if (args[i] == '\'' && !dquotes)
		{
			current->quotes = get_quote_type(args, '\'', &squotes, &i);
			if (current->quotes != NO_QUOTES)
				break ;
		}
		else if (args[i] == '"' && !squotes)
		{
			current->quotes = get_quote_type(args, '"', &dquotes, &i);
			if (current->quotes != NO_QUOTES)
				break ;
		}
		i++;
	}
}

int	get_size(char *args)
{
	int		size;
	int		i;
	t_bool	squotes;
	t_bool	dquotes;

	i = 0;
	size = 0;
	squotes = FALSE;
	dquotes = FALSE;
	while (args[i] != '\0')
	{
		if (args[i] == '\'' && !dquotes)
			squotes = !squotes;
		else if (args[i] == '"' && !squotes)
			dquotes = !dquotes;
		else
			size++;
		i++;
	}
	return (size);
}

char	*rm_quotes(char *args, int size)
{
	int		i;
	int		j;
	t_bool	squotes;
	t_bool	dquotes;
	char	*new_arg;

	i = 0;
	j = 0;
	squotes = FALSE;
	dquotes = FALSE;
	new_arg = (char *)malloc(sizeof(char) * (size + 1));
	if (new_arg == NULL)
		return (NULL);
	while (j < size)
	{
		if (args[i] == '\'' && !dquotes)
			squotes = !squotes;
		else if (args[i] == '"' && !squotes)
			dquotes = !dquotes;
		else
			new_arg[j++] = args[i];
		i++;
	}
	new_arg[j] = '\0';
	return (new_arg);
}
