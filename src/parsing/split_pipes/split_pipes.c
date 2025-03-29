/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 15:24:11 by aroullea          #+#    #+#             */
/*   Updated: 2025/03/29 17:29:27 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_pipes(t_token *tokens)
{
	t_token		*current;
	t_command	*cmds;
	t_arg_type	*arg;

	current = tokens;
	arg = current->arg_type;
	cmds = NULL;
	while (current != NULL)
	{
		if (cmds == NULL)
		{
			create_cmd_list(cmds, tokens);
			if (cmds == NULL)
				return (NULL);
		}
		if (arg == COMMAND || arg == OPTION || arg == ARGUMENT)
			add_to_argv(cmds, current);
	}
}
