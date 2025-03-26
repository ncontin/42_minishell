/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:38:18 by aroullea          #+#    #+#             */
/*   Updated: 2025/03/26 15:42:40 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	is_operator_followed_by_arg(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current != NULL)
	{
		if ((current->operator > 0) && (current->next == NULL))
		{
			current = current->next;
			write(2, "syntax error near unexpected token `newline'\n", 45);
			return (FALSE);
		}
		current = current->next;
	}
	return (TRUE);
}

static t_bool	is_both_operator(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current != NULL)
	{
		if ((current->operator > 0) &&
				(current->next != NULL && current->next->operator != NONE))
		{
			current = current->next;
			write(2, "syntax error near unexpected token `", 36);
			write(2, current->argument, ft_strlen(current->argument));
			write(2, "\"\n", 2);
			return (FALSE);
		}
		current = current->next;
	}
	return (TRUE);
}

t_bool	is_valid_token(t_token *tokens)
{
	if (is_both_operator(tokens) == FALSE)
		return (FALSE);
	if (is_operator_followed_by_arg(tokens) == FALSE)
		return (FALSE);
	return (TRUE);
}
