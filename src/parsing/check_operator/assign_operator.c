/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_operator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:57:16 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/07 18:59:38 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	operator_type_next(t_token *current)
{
	if (ft_strncmp (current->argument, ">>", 3) == 0)
	{
		free(current->argument);
		current->argument = NULL;
		current->operator = APPEND;
		return ;
	}
	else if (ft_strncmp (current->argument, "<<", 3) == 0)
	{
		free(current->argument);
		current->argument = NULL;
		current->operator = HEREDOC;
		return ;
	}
}

static void	operator_type(t_token *current)
{
	if (current->argument == NULL)
		return ;
	if (ft_strncmp(current->argument, ">", 2) == 0)
	{
		free(current->argument);
		current->argument = NULL;
		current->operator = OUTPUT;
		return ;
	}
	else if (ft_strncmp(current->argument, "<", 2) == 0)
	{
		free(current->argument);
		current->argument = NULL;
		current->operator = INPUT;
		return ;
	}
	else if (ft_strncmp(current->argument, "|", 2) == 0)
	{
		free(current->argument);
		current->argument = NULL;
		current->operator = PIPE;
		return ;
	}
	operator_type_next(current);
}

void	assign_operator(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current != NULL)
	{
		if (current->quotes == NO_QUOTES)
			operator_type(current);
		current = current->next;
	}
}
