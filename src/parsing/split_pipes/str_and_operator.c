/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_and_operator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 17:42:04 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/18 14:46:53 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_new(t_command **new)
{
	free((*new)->arg_quotes);
	free((*new)->argv);
	free(*new);
	*new = NULL;
}

static void	arg_count(t_token *tokens, int *count_arg, int *count_operator)
{
	t_token		*current;
	t_arg_type	type;

	current = tokens;
	while (current != NULL && current->operator != PIPE)
	{
		type = current->arg_type;
		if (current->operator == NONE && (type == COMMAND || type == OPTION
				|| type == ARGUMENT || type == ENV_VAR))
			(*count_arg)++;
		else if (current->operator != NONE)
			(*count_operator)++;
		current = current->next;
	}
}

static int	alloc_argv(t_command *new, int nb_args)
{
	new->argv = (char **)malloc(sizeof(char *) * (nb_args + 2));
	if (new->argv == NULL)
	{
		free(new);
		new = NULL;
		return (1);
	}
	new->arg_quotes = (t_quotes *)malloc(sizeof(t_quotes *) * (nb_args));
	if (new->arg_quotes == NULL)
	{
		free(new->argv);
		free(new);
		new = NULL;
		return (1);
	}
	return (0);
}

static int	alloc_operator(t_command *new, int nb_operator)
{
	new->operator = (t_operator *) malloc(sizeof(t_operator *) * nb_operator);
	if (new->operator == NULL)
	{
		return (1);
	}
	new->file = (char **)malloc(sizeof(char *) * nb_operator);
	if (new->file == NULL)
	{
		free(new->operator);
		return (1);
	}
	return (0);
}

int	str_and_operator(t_command *new, t_token *tokens)
{
	int	nb_args;
	int	nb_operator;

	nb_args = 0;
	nb_operator = 0;
	arg_count(tokens, &nb_args, &nb_operator);
	if (nb_args > 0)
	{
		if (alloc_argv(new, nb_args) == 1)
			return (1);
	}
	if (nb_operator > 0)
	{
		if (alloc_operator(new, nb_operator) == 1)
		{
			if (nb_args > 0)
				free_new(&new);
			return (1);
		}
	}
	new->nb_operator = nb_operator;
	return (0);
}
