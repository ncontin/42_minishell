/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_operator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:57:16 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/18 14:57:44 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	operator_type_next(t_token *current, size_t len)
{
	if (ft_strncmp(current->argument, ">>", len) == 0)
	{
		free(current->argument);
		current->argument = NULL;
		current->operator = APPEND;
		return ;
	}
	else if (ft_strncmp(current->argument, "<<", len) == 0)
	{
		free(current->argument);
		current->argument = NULL;
		current->operator = HEREDOC;
		return ;
	}
}

static void	operator_type(t_token *current, size_t len)
{
	if (current->argument == NULL || len == 0)
		return ;
	if (ft_strncmp(current->argument, ">", len) == 0)
	{
		free(current->argument);
		current->argument = NULL;
		current->operator = OUTPUT;
		return ;
	}
	else if (ft_strncmp(current->argument, "<", len) == 0)
	{
		free(current->argument);
		current->argument = NULL;
		current->operator = INPUT;
		return ;
	}
	else if (ft_strncmp(current->argument, "|", len) == 0)
	{
		free(current->argument);
		current->argument = NULL;
		current->operator = PIPE;
		return ;
	}
	operator_type_next(current, len);
}

void	assign_operator(t_token *tokens)
{
	t_token	*current;
	size_t	len;

	current = tokens;
	while (current != NULL)
	{
		if (current->quotes == NO_QUOTES)
		{
			len = ft_strlen(current->argument);
			operator_type(current, len);
		}
		current = current->next;
	}
}
