/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 15:24:11 by aroullea          #+#    #+#             */
/*   Updated: 2025/03/30 18:00:16 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_to_argv(t_command *new, t_token *current) 
{
	int		i;
	char	*src;

	i = 0;
	src = current->argument;
	new->argv[i] = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (argv[i] == NULL)
		return (NULL);

}

void	split_pipes(t_token *tokens)
{
	t_token		*current;
	t_command	*cmds;
	t_command	*new;
	t_arg_type	*arg;

	current = tokens;
	arg = current->arg_type;
	cmds = NULL;
	new = NULL;
	while (current != NULL)
	{
		if (cmds == NULL)
		{
			new = create_cmd_list(cmds, tokens);
			if (new == NULL)
				return (NULL);
		}
		if (arg == COMMAND || arg == OPTION || arg == ARGUMENT || arg = ENV_VAR)
			add_to_argv(new, current);
	}
}
