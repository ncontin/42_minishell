/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:29:01 by aroullea          #+#    #+#             */
/*   Updated: 2025/03/21 11:27:40 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
