/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:38:28 by ncontin           #+#    #+#             */
/*   Updated: 2025/03/26 18:01:35 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(t_token *token)
{
	t_token	*current;

	current = token;
	while (current != NULL)
	{
		token = token->next;
		free(current->argument);
		free(current);
		current = token;
	}
}

void	msg_and_free(t_token *tokens)
{
	write(2, "Memory allocation failed to create arg\n", 39);
	free_token(tokens);
}
