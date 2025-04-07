/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_and_operator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 17:42:04 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/07 16:57:57 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	arg_count(t_token *tokens, int *count_arg, int *count_operator)
{
	t_token		*current;
	t_arg_type	type;

	current = tokens;
	while (current != NULL && current->operator != PIPE)
	{
		type = current->arg_type;
		if (current->operator == NONE
			&& (type == COMMAND || type == OPTION || type == ARGUMENT
				|| type == ENV_VAR))
			(*count_arg)++;
		else if (current->operator != NONE)
			(*count_operator)++;
		current = current->next;
	}
}

static t_bool	alloc_operator(t_command *new, int nb_operator, t_token *tokens)
{
	new->operator = (t_operator *)malloc(sizeof(t_operator *) * nb_operator);
	if (new->operator == NULL)
	{
		free(tokens);
		return (FALSE);
	}
	new->file = (char **)malloc(sizeof(char *) * nb_operator);
	if (new->operator == NULL)
	{
		free(tokens);
		return (FALSE);
	}
	return (TRUE);
}

t_bool	str_and_operator(t_command *new, t_token *tokens)
{
	int	nb_args;
	int	nb_operator;

	nb_args = 0;
	nb_operator = 0;
	arg_count(tokens, &nb_args, &nb_operator);
	if (nb_args > 0)
	{
		new->argv = (char **)malloc(sizeof(char *) * (nb_args + 2));
		if (new->argv == NULL)
		{
			free(tokens);
			return (FALSE);
		}
	}
	if (nb_operator > 0)
	{
		if (alloc_operator(new, nb_operator, tokens) == FALSE)
			return (FALSE);
	}
	new->nb_operator = nb_operator;
	return (TRUE);
}
