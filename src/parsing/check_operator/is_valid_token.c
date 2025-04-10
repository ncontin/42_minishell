/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:38:18 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/10 16:45:53 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	check_same_operator(t_operator first, t_operator second)
{
	if ((first >= 1 && first <= 4) && (second >= 1 && second <= 4))
		return (TRUE);
	if (first == PIPE && second == PIPE)
		return (TRUE);
	return (FALSE);
}

static t_bool	is_both_operator(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current != NULL)
	{
		if ((current->operator> 0) && (current->next != NULL
				&& current->next->operator!= NONE))
		{
			if (check_same_operator(current->operator,
					current->next->operator) == TRUE)
			{
				current = current->next;
				write(2, "syntax error near unexpected token `", 36);
				write(2, current->argument, ft_strlen(current->argument));
				write(2, "\"\n", 2);
				return (FALSE);
			}
		}
		current = current->next;
	}
	return (TRUE);
}

static t_bool	is_operator_followed_by_arg(t_token *tokens)
{
	t_token	*current;
	t_bool	check_operator;

	current = tokens;
	while (current != NULL)
	{
		check_operator = ((current->operator> 0) && (current->operator<5));
		if (check_operator && (current->next->argument == NULL))
		{
			write(2, "syntax error near unexpected token `newline'\n", 45);
			return (FALSE);
		}
		if (current->operator== PIPE && current->next == NULL)
		{
			write(2, "syntax error near unexpected token \"|\"\n", 40);
			return (FALSE);
		}
		current = current->next;
	}
	return (TRUE);
}

t_bool	is_valid_token(t_token *tokens)
{
	if (tokens->operator== PIPE ||(tokens->operator> 0 && tokens->next == NULL))
	{
		write(2, "syntax error near unexpected token \"|\"\n", 40);
		return (FALSE);
	}
	if (is_both_operator(tokens) == FALSE)
		return (FALSE);
	if (is_operator_followed_by_arg(tokens) == FALSE)
		return (FALSE);
	return (TRUE);
}
