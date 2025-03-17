/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:29:01 by aroullea          #+#    #+#             */
/*   Updated: 2025/03/12 17:35:28 by aroullea         ###   ########.fr       */
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
