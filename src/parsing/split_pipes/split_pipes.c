/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 15:24:11 by aroullea          #+#    #+#             */
/*   Updated: 2025/03/31 14:16:53 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*split_pipes(t_token *tokens)
{
	t_token		*current;
	t_command	*cmds;
	t_command	*new;
	int			i;

	i = 0;
	cmds = NULL;
	new = NULL;
	current = tokens;
	while (current != NULL)
	{
		if (new == NULL)
		{
			new = create_cmd_list(&cmds, tokens);
			if (new == NULL)
			{
				free_token(tokens);
				return (NULL);
			}
			i = 0;
		}
		if (current->arg_type == COMMAND || current->arg_type == OPTION
			|| current->arg_type == ARGUMENT || current->arg_type == ENV_VAR)
		{
			new->argv[i++] = current->argument;
			new->argv[i] = NULL;
		}
		else if (current->operator == OUTPUT || current->operator == INPUT
			|| current->operator == APPEND || current->operator == HEREDOC)
			new->operator = current->operator;
		else if (current->operator == PIPE)
		{
			i = 0;
			new = new->next;
		}
		current = current->next;
	}
	return (cmds);
}
