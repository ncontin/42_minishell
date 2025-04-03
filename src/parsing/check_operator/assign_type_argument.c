/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_type_argument.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:27:12 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/03 12:12:02 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	assign_next(t_token *current)
{
	if (current->prev && (current->prev->operator == OUTPUT
			|| current->prev->operator == INPUT
			|| current->prev->operator == APPEND))
		current->arg_type = FILENAME;
	else if (!current->prev
		|| (current->prev && current->prev->operator == PIPE))
		current->arg_type = COMMAND;
	else if (current->argument != NULL && current->argument[0] == '-')
		current->arg_type = OPTION;
	else
		current->arg_type = ARGUMENT;
}

void	assign_type_argument(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current != NULL)
	{
		if (current->operator == PIPE)
			current->arg_type = PIPE_OPERATOR;
		else if (current->argument != NULL && current->argument[0] == '$')
			current->arg_type = ENV_VAR;
		else if (current->operator == OUTPUT || current->operator == INPUT
			|| current->operator == APPEND || current->operator == HEREDOC)
			current->arg_type = REDIRECTION;
		else if (current->prev && current->prev->operator == HEREDOC)
			current->arg_type = HERE_DOC_LIMITER;
		else
			assign_next(current);
		current = current->next;
	}
}
