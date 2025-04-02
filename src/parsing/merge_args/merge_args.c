/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:26:03 by aroullea          #+#    #+#             */
/*   Updated: 2025/03/30 17:53:43 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	delete_list(t_token *token)
{
	t_token	*current;
	t_token	*following;

	current = token;
	following = token->next;
	token = token->prev;
	token->next = following;
	if (following != NULL)
		following->prev = token;
	free(current);
}

static t_bool	concat_args(t_token *token, t_token *following, char *str)
{
	t_token	*current;
	t_token	*deleted;

	current = token;
	while (1)
	{
		str = ft_strjoin(current->argument, following->argument);
		if (str == NULL)
			return (FALSE);
		else
		{
			free(current->argument);
			free(following->argument);
			current->argument = str;
		}
		if (following->linked == FALSE)
		{
			delete_list(following);
			break ;
		}
		deleted = following;
		following = following->next;
		delete_list(deleted);
	}
	return (TRUE);
}

t_token	*merge_args(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current != NULL)
	{
		if (current->linked == TRUE)
		{
			if (concat_args(current, current->next, NULL) == FALSE)
			{
				free(tokens);
				return (NULL);
			}
		}
		current = current->next;
	}
	return (tokens);
}
