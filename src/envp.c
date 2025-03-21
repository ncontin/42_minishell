/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:20:38 by ncontin           #+#    #+#             */
/*   Updated: 2025/03/21 14:28:01 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_node	*find_last(t_env_node **my_envp)
{
	t_env_node	*last;

	last = *my_envp;
	while (last->next)
	{
		last = last->next;
	}
	return (last);
}

void	free_stack(t_env_node **my_envp)
{
	t_env_node	*current;
	t_env_node	*next;

	current = *my_envp;
	while (current)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
	*my_envp = NULL;
	free(my_envp);
}

t_env_node	**copy_envp(char **envp)
{
	t_env_node	**ft_envp;
	t_env_node	*node;
	t_env_node	*last;
	int			i;
	int			equal_index;

	ft_envp = malloc(sizeof(t_env_node *));
	if (!ft_envp)
		return (NULL);
	*ft_envp = NULL;
	i = 0;
	while (envp[i])
	{
		node = malloc(sizeof(t_env_node));
		if (!node)
			return (NULL);
		equal_index = find_equal(envp[i]);
		node->key = ft_substr(envp[i], 0, equal_index);
		node->value = ft_substr(envp[i], equal_index, ft_strlen(envp[i])
				- equal_index);
		node->next = NULL;
		if (!(*ft_envp))
			*ft_envp = node;
		else
		{
			last = find_last(ft_envp);
			last->next = node;
		}
		i++;
	}
	return (ft_envp);
}

void	init_envp(t_env *lst_env)
{
	lst_env->envp_cp = copy_envp(lst_env->envp);
}
