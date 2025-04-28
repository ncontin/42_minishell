/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 15:24:11 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/28 19:59:25 by aroullea         ###   ########.fr       */
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
			return ;
		}
	}
}

static void	handle_command(t_command *new, t_token *current, int *i)
{
	new->argv[*i] = current->argument;
	new->arg_quotes[(*i)++] = current->quotes;
	new->argv[*i] = NULL;
}

static void	handle_operator(t_command *new, t_token *current, int *j)
{
	new->operator[*j] = current->operator;
	if (current->operator == HEREDOC && current->next != NULL)
	{
		if (current->next->hd_expand == TRUE)
			new->limiter_quotes = current->next->quotes;
		else
			new->limiter_quotes = SINGLE;
		new->check_here_doc = TRUE;
	}
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
		if (is_command(current->arg_type) == TRUE)
			handle_command(new, current, &i);
		else if (is_recognized_operator(current->operator) == TRUE)
			handle_operator(new, current, &j);
		else if (is_filename_or_limiter(current->arg_type) == TRUE)
			new->file[j++] = current->argument;
		else if (current->operator == PIPE)
			new = handle_pipe(new, &i, &j);
		current = current->next;
	}
	return (cmds);
}
