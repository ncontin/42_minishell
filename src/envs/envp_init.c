/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:20:38 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/01 14:51:22 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	copy_env(t_env_node **ft_envp, char *env)
{
	t_env_node	*node;
	t_env_node	*last;

	node = malloc(sizeof(t_env_node));
	if (!node)
		return ;
	node->key = get_key(env);
	node->value = get_value(env);
	node->next = NULL;
	if (!(*ft_envp))
		*ft_envp = node;
	else
	{
		last = find_last(ft_envp);
		last->next = node;
	}
}

t_env_node	**convert_envp_to_list(char **envp)
{
	t_env_node	**ft_envp;
	int			i;

	ft_envp = malloc(sizeof(t_env_node *));
	if (!ft_envp)
		return (NULL);
	*ft_envp = NULL;
	i = 0;
	while (envp[i])
	{
		copy_env(ft_envp, envp[i]);
		i++;
	}
	return (ft_envp);
}

void	init_envp(t_env *lst_env)
{
	lst_env->envp_cp = convert_envp_to_list(lst_env->envp);
}
