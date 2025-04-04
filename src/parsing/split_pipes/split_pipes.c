/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 15:24:11 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/04 15:38:41 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_argument(t_command *new, t_token *current, int *i)
{
	new->argv[(*i)++] = current->argument;
	new->argv[*i] = NULL;
}

static void	new_cmd(t_command **new, t_command **cmds, t_token *tokens, int *i)
{
	if (*new == NULL)
	{
		*new = create_cmd_list(cmds, tokens);
		if (*new == NULL)
		{
			if (*cmds != NULL)
				free_commands(*cmds);
			free_token(tokens);
			return ;
		}
		*i = 0;
	}
}

static t_command	*handle_pipe(t_command *new, int *i)
{
	*i = 0;
	new = new->next;
	return (new);
}

t_command	*split_pipes(t_token *tokens, t_command *cmds, t_command *new)
{
	t_token		*current;
	int			i;

	i = 0;
	current = tokens;
	while (current != NULL)
	{
		new_cmd(&new, &cmds, tokens, &i);
		if (new == NULL)
			return (NULL);
		if (current->arg_type == COMMAND || current->arg_type == OPTION
			|| current->arg_type == ARGUMENT || current->arg_type == ENV_VAR)
			handle_argument(new, current, &i);
		else if (current->operator == OUTPUT || current->operator == INPUT
			|| current->operator == APPEND || current->operator == HEREDOC)
			new->operator = current->operator;
		else if (current->arg_type == FILENAME || current->arg_type == HERE_DOC_LIMITER)
			new->file = current->argument;
		else if (current->operator == PIPE)
			new = handle_pipe(new, &i);
		current = current->next;
	}
	return (cmds);
}
