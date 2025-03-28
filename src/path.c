/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:57:25 by aroullea          #+#    #+#             */
/*   Updated: 2025/03/28 15:40:24 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_path(char **envp, t_env *lst_env)
{
	char	**mypath;
	char	*env_path;

	mypath = NULL;
	lst_env->envp = envp;
	env_path = getenv("PATH");
	mypath = ft_split(env_path, ':');
	if (mypath == NULL)
		error_msg("Path : memory allocation failed\n", 12);
	lst_env->path = mypath;
}
