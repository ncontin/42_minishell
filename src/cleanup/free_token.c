/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:38:28 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/02 19:08:37 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(t_token *token)
{
	t_token	*current;
	t_token	*next;

	if (!token)
		return ;
	current = token;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

void	msg_and_free(t_token *tokens)
{
	write(2, "Memory allocation failed to create arg\n", 39);
	free_token(tokens);
}
