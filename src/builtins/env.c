/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:38:46 by ncontin           #+#    #+#             */
/*   Updated: 2025/03/20 17:47:17 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char	**copy_env(char **envp)
// {
// 	int		i;
// 	char	**sorted_env;

// 	i = 0;
// 	while (envp[i])
// 		i++;
// 	sorted_env = malloc(sizeof(char *) * (i + 1));
// 	if (!sorted_env)
// 		return (NULL);
// 	i = 0;
// 	while (envp[i])
// 	{
// 		sorted_env[i] = ft_strdup(envp[i]);
// 		i++;
// 	}
// 	sorted_env[i] = NULL;
// 	return (sorted_env);
// }

// void	ft_env(char **envp)
// {
// 	int	i;

// 	// char	**sorted_env;
// 	// sorted_env = copy_env(envp);
// 	i = 0;
// 	while (envp[i])
// 	{
// 		if (ft_strlen(envp[i]) == 0)
// 			i++;
// 		printf("%s\n", envp[i]);
// 		i++;
// 	}
// 	// do env
// }

void	ft_env(t_env_node **envp_cp)
{
	print_env_stack(envp_cp);
}
