/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:20:38 by ncontin           #+#    #+#             */
/*   Updated: 2025/03/21 12:41:48 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env_stack(t_env_node **env_stack)
{
	t_env_node	*current;

	current = *env_stack;
	while (current)
	{
		printf("%s\n", current->env_string);
		current = current->next;
	}
}

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
		free(current->env_string);
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
		node->env_string = ft_strdup(envp[i]);
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
