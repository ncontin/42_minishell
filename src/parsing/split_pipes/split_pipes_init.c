/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipes_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 15:52:01 by aroullea          #+#    #+#             */
/*   Updated: 2025/03/31 18:18:14 by aroullea         ###   ########.fr       */
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
	{
		free_token(tokens);
		return (NULL);
	}
	new_cmds->argv = NULL;
	new_cmds->operator = 0;
	new_cmds->next = NULL;
	new_cmds->file = NULL;
	cmd_add_new(cmds, new_cmds);
	create_argv(new_cmds, tokens);
	if (new_cmds->argv == NULL)
	{
		free_commands(*cmds);
		return (NULL);
	}
	return (new_cmds);
}
