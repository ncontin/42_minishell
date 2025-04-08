/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:43:11 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/08 16:03:22 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_stack(t_env_node **my_envp)
{
	t_env_node	*current;
	t_env_node	*next;

	if (!my_envp)
		return ;
	current = *my_envp;
	while (current)
	{
		next = current->next;
		if (current->value)
			free(current->value);
		free(current->key);
		free(current);
		current = next;
	}
	*my_envp = NULL;
	free(my_envp);
}
