/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_dollar_alone.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:19:29 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/24 16:41:27 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_dollar_alone(t_mini *mini)
{
	t_token *current;
	t_token	*next;
	char	*str;

	current = mini->tokens;
	while (current != NULL)
	{
		next = NULL;
		if (current->argument)
		{
			str = current->argument;
			if ((ft_strncmp(str, "$", ft_strlen(str) + 1) == 0) && current->linked == TRUE)
			{
				next = current->next;
				current->prev->next = next;
				next->prev = current->prev;
				free(current->argument);
				free(current);
				current = NULL;
			}
		}
		if (current == NULL && next != NULL)
			current = next;
		else
			current = current->next;
	}
}
