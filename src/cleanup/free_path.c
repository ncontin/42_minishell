/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:29:01 by aroullea          #+#    #+#             */
/*   Updated: 2025/03/26 16:42:01 by ncontin          ###   ########.fr       */
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

void	free_path(t_env *lst_env)
{
	int	i;

	i = 0;
	while (lst_env->path[i] != NULL)
	{
		free(lst_env->path[i]);
		i++;
	}
	free(lst_env->path);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	msg_and_free(t_token *tokens)
{
	write(2, "Memory allocation failed to create arg\n", 39);
	free_token(tokens);
}
