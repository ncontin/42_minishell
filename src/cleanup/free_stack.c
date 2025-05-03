/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:43:11 by ncontin           #+#    #+#             */
/*   Updated: 2025/05/03 11:49:40 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_stack(t_env *head)
{
	t_env	*current;
	t_env	*next;

	if (!head)
		return ;
	current = head;
	while (current != NULL)
	{
		next = current->next;
		if (current->value)
			free(current->value);
		free(current->key);
		free(current);
		current = next;
	}
}
