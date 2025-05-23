/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipes_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 15:52:01 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/18 14:15:46 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cmd_add_new(t_command **head, t_command *new)
{
	t_command	*current;

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

t_command	*create_cmd_list(t_command **cmds, t_token *tokens)
{
	t_command	*new_cmds;

	new_cmds = (t_command *)malloc(sizeof(t_command));
	if (new_cmds == NULL)
		return (NULL);
	new_cmds->nb_operator = 0;
	new_cmds->here_doc_fd = -1;
	new_cmds->argv = NULL;
	new_cmds->operator = NULL;
	new_cmds->next = NULL;
	new_cmds->prev = NULL;
	new_cmds->file = NULL;
	new_cmds->arg_quotes = NULL;
	new_cmds->check_here_doc = FALSE;
	if (str_and_operator(new_cmds, tokens) == 1)
		return (NULL);
	cmd_add_new(cmds, new_cmds);
	return (new_cmds);
}
