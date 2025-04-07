/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_operator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:38:39 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/07 10:46:53 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	operator_count(t_token *tokens)
{
	t_token	*current;
	int		count;

	current = tokens;
	while (current != NULL && current->operator != PIPE)
	{
		if (current->operator != NONE)
			count++;
		current = current->next;
	}
	return (count);
}

void	create_operator(t_command *new, t_token *tokens)
{
	int	nb_operator;

	nb_operator = operator_count(tokens);
	if (nb_operator > 0)
	{
		new->operator = (t_operator *)malloc(sizeof(t_operator * nb_operator));
		if (new->operator == NULL)
		{
			free(tokens);
			return ;
		}
	}
}
