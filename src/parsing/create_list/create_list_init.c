/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 15:52:01 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/28 19:40:09 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*init_new_list(t_token *head)
{
	t_token	*current;

	current = (t_token *)malloc(sizeof(t_token));
	if (current == NULL)
	{
		write(2, "Memory allocation failed to create list\n", 40);
		free_token_argument(head);
		free_token(head);
		return (NULL);
	}
	current->argument = NULL;
	current->quotes = NO_QUOTES;
	current->linked = FALSE;
	current->operator = NONE;
	current->next = NULL;
	current->prev = NULL;
	current->hd_expand = TRUE;
	return (current);
}

void	lst_add_new(t_token **head, t_token *new)
{
	t_token	*current;

	if (head)
	{
		if (*head)
		{
			current = *head;
			while (current->next != NULL)
				current = current->next;
			current->next = new;
			new->prev = current;
		}
		else
			*head = new;
	}
}
