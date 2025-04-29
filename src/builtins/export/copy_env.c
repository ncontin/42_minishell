/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 06:40:44 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/29 06:42:16 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env_node	*create_env_node(t_env_node *current)
{
	t_env_node	*node;

	node = malloc(sizeof(t_env_node));
	if (!node)
		return (NULL);
	node->key = ft_strdup(current->key);
	if (!node->key)
	{
		free(node);
		return (NULL);
	}
	if (current->value)
	{
		node->value = ft_strdup(current->value);
		if (!node->value)
		{
			free(node->key);
			free(node);
			return (NULL);
		}
	}
	else
		node->value = NULL;
	node->next = NULL;
	return (node);
}

static void	append_env_node(t_env_node **ft_envp, t_env_node *node)
{
	t_env_node	*last;

	if (!(*ft_envp))
		*ft_envp = node;
	else
	{
		last = find_last(ft_envp);
		last->next = node;
	}
}

static int	copy_env(t_env_node *current, t_env_node **ft_envp, t_mini *mini)
{
	t_env_node	*node;

	node = create_env_node(current);
	if (!node)
	{
		copy_env_node_error(ft_envp, mini);
		return (1);
	}
	append_env_node(ft_envp, node);
	return (0);
}

t_env_node	**copy_envp_list(t_env_node **envp_cp, t_mini *mini)
{
	t_env_node	**ft_envp;
	t_env_node	*current;

	current = *envp_cp;
	ft_envp = malloc(sizeof(t_env_node *));
	if (!ft_envp)
	{
		ft_envp_error(mini);
		return (NULL);
	}
	*ft_envp = NULL;
	while (current)
	{
		if (copy_env(current, ft_envp, mini) == 1)
			return (NULL);
		current = current->next;
	}
	return (ft_envp);
}
