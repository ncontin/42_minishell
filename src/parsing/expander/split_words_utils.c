/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_words_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:45:19 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/24 11:49:11 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(char *arg)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->argument = ft_strdup(arg);
	if (!new_token->argument)
	{
		free(new_token);
		return (NULL);
	}
	new_token->quotes = NO_QUOTES;
	new_token->linked = FALSE;
	new_token->operator = NONE;
	new_token->next = NULL;
	new_token->prev = NULL;
	return (new_token);
}

void	add_new_token(t_token *token, char *word, t_token *next_og)
{
	t_token	*current;
	t_token	*new;

	new = create_token(word);
	current = token;
	current->next = new;
	new->next = next_og;
	new->prev = current;
	if (next_og)
		next_og->prev = new;
}
