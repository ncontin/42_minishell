/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 06:40:44 by aroullea          #+#    #+#             */
/*   Updated: 2025/05/03 10:33:56 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*create_env_node(t_env *current)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
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

static void	append_env_node(t_env **head, t_env **new, t_env **end)
{
    if (*head == NULL)
    {
        *head = *new;
        *end = *new;
    }
    else
    {
        (*end)->next = *new;
        *end = *new;
    }
}

t_env	*copy_envp_list(t_env *envp_cp, t_mini *mini)
{
	t_env	*current;
	t_env	*new;
	t_env	*head;
	t_env	*end;

	current = envp_cp;
	head = NULL;
	new = NULL;
	end = NULL;
	while (current != NULL)
	{
		new = create_env_node(current);
		if (new == NULL)
		{
			copy_env_node_error(head, mini);
			return (NULL);
		}
		append_env_node(&head, &new, &end);
		current = current->next;
	}
	return (head);
}
