/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 15:24:11 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/07 19:34:54 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	new_cmd(t_command **new, t_command **cmds, t_token *tokens)
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
	}
}

static void	handle_argument(t_command *new, t_token *current, int *i)
{
	new->argv[*i] = current->argument;
	new->arg_quotes[(*i)++] = current->quotes;
	new->argv[*i] = NULL;
}

static void	handle_operator(t_command *new, t_token *current, int *j)
{
	new->operator[*j] = current->operator;
	if (current->operator == HEREDOC)
		new->limiter_quotes = current->quotes;
}

static t_command	*handle_pipe(t_command *new, int *i, int *j)
{
	*i = 0;
	*j = 0;
	new = new->next;
	return (new);
}

t_command	*split_pipe(t_token *tokens, t_command *cmds, t_command *new, int i)
{
	t_token		*current;
	int			j;

	j = 0;
	current = tokens;
	while (current != NULL)
	{
		new_cmd(&new, &cmds, current);
		if (new == NULL)
			return (NULL);
		if (current->arg_type == COMMAND || current->arg_type == OPTION
			|| current->arg_type == ARGUMENT || current->arg_type == ENV_VAR)
			handle_argument(new, current, &i);
		else if (current->operator == OUTPUT || current->operator == INPUT
			|| current->operator == APPEND || current->operator == HEREDOC)
			handle_operator(new, current, &j);
		else if (current->arg_type == FILENAME
			|| current->arg_type == HERE_DOC_LIMITER)
			new->file[j++] = current->argument;
		else if (current->operator == PIPE)
			new = handle_pipe(new, &i, &j);
		current = current->next;
	}
	return (cmds);
}
