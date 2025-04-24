/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_dollar_alone.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:19:29 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/24 17:40:55 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_new_line(t_token *current)
{
	if (ft_strncmp("\\n", current->next->argument, 3) == 0
		|| ft_strncmp("\\r", current->next->argument, 3) == 0
		|| ft_strncmp("\\t", current->next->argument, 3) == 0)
		return (1);
	return (0);
}

static void	remove_dollar(t_token **current, t_token **next)
{
	(*next) = (*current)->next;
	(*current)->prev->next = *next;
	(*next)->prev = (*current)->prev;
	free((*current)->argument);
	free(*current);
	*current = NULL;
}

void	is_dollar_alone(t_mini *mini)
{
	t_token	*current;
	t_token	*next;
	char	*str;

	current = mini->tokens;
	while (current != NULL)
	{
		next = NULL;
		if (current->argument)
		{
			str = current->argument;
			if ((ft_strncmp(str, "$", ft_strlen(str) + 1) == 0)
				&& current->linked == TRUE)
			{
				if (is_new_line(current) == 0)
					remove_dollar(&current, &next);
			}
		}
		if (current == NULL && next != NULL)
			current = next;
		else
			current = current->next;
	}
}
