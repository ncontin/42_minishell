/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 17:42:04 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/03 16:27:46 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	arg_count(t_token *tokens)
{
	t_token		*current;
	t_arg_type	type;
	int			count;

	count = 0;
	current = tokens;
	while (current != NULL && current->operator != PIPE)
	{
		type = current->arg_type;
		if (current->operator == NONE
			&& (type == COMMAND || type == OPTION || type == ARGUMENT
				|| type == ENV_VAR))
			count++;
		current = current->next;
	}
	return (count);
}

void	create_argv(t_command *new, t_token *tokens)
{
	int	nb_args;

	nb_args = arg_count(tokens);
	if (nb_args > 0)
	{
		new->argv = (char **)malloc(sizeof(char *) * (nb_args + 2));
		if (new->argv == NULL)
		{
			free(tokens);
			return ;
		}
	}
	new->argc = nb_args;
}
