/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 15:24:11 by aroullea          #+#    #+#             */
/*   Updated: 2025/03/31 12:07:49 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*split_pipes(t_token *tokens)
{
	t_token		*current;
	t_command	*cmds;
	t_command	*new;
	t_arg_type	arg;
	int			i;

	i = 0;
	current = tokens;
	cmds = NULL;
	new = NULL;
	while (current != NULL)
	{
		arg = current->arg_type;
		if (new == NULL)
		{
			new = create_cmd_list(&cmds, tokens);
			if (new == NULL)
			{
				free(tokens);
				return (NULL);
			}
		}
		if (arg == COMMAND || arg == OPTION || arg == ARGUMENT || arg == ENV_VAR)
		{
			new->argv[i] = current->argument; 
			i++;
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
