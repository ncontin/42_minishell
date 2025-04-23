/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:26:03 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/22 18:12:11 by ncontin          ###   ########.fr       */
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

t_bool	merge_args(t_token **tokens)
{
	t_token	*current;
	t_bool	is_arg;

	current = *tokens;
	while (current != NULL)
	{
		is_arg = (current->next != NULL && current->next->argument != NULL);
		if (current->linked == TRUE && is_arg)
		{
			if (concat_args(current, current->next, NULL) == FALSE)
			{
				free_token_argument(*tokens);
				free_token(*tokens);
				return (FALSE);
			}
		}
		current = current->next;
	}
	return (TRUE);
}
