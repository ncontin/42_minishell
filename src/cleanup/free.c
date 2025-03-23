/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:29:01 by aroullea          #+#    #+#             */
/*   Updated: 2025/03/23 18:11:42 by aroullea         ###   ########.fr       */
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

void	free_struct(t_env *lst_env)
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

void	free_tokens(t_token *tokens_info)
{
	int	i;

	i = 0;
	while (tokens_info[i].argument != NULL)
	{
		free(tokens_info[i].argument);
		i++;
	}
	free(tokens_info);
}
