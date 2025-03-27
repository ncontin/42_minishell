/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:29:01 by aroullea          #+#    #+#             */
/*   Updated: 2025/03/27 08:59:40 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
