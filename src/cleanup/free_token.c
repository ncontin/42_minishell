/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:38:28 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/17 10:52:14 by aroullea         ###   ########.fr       */
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

void	free_token_argument(t_token *token)
{
	t_token	*current;

	if (!token)
		return ;
	current = token;
	while (current != NULL)
	{
		if (current->argument != NULL)
			free(current->argument);
		current = current->next;
	}
}

void	msg_and_free(t_token *tokens)
{
	write(2, "Create_list :", 13);
	write(2, "memory allocation failed to create arg\n", 39);
	free_token_argument(tokens);
	free_token(tokens);
}
