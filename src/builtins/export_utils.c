/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:47:09 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/28 10:25:15 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(t_env_node **sorted_envp_cp, char **args)
{
	t_env_node	*current;

	if (!(*sorted_envp_cp) && !sorted_envp_cp)
		return ;
	if (args[0] && !args[1])
	{
		if (sorted_envp_cp && *sorted_envp_cp)
		{
			current = *sorted_envp_cp;
			while (current)
			{
				if (current->key)
					printf("declare -x %s", current->key);
				if (current->value)
					printf("=\"%s\"", current->value);
				printf("\n");
				current = current->next;
			}
		}
	}
}

t_env_node	*find_min(t_env_node **envp_cp)
{
	t_env_node	*current;
	t_env_node	*min;

	if (!*envp_cp)
		return (NULL);
	min = *envp_cp;
	current = (*envp_cp)->next;
	while (current)
	{
		if (ft_strncmp(min->key, current->key, find_min_len(min->key,
					current->key)) > 0)
			min = current;
		current = current->next;
	}
	return (min);
}

static int	copy_env_node(t_env_node *current, t_env_node **ft_envp, t_mini *mini)
{
	t_env_node	*node;
	t_env_node	*last;

	node = malloc(sizeof(t_env_node));
	if (!node)
	{
		copy_env_node_error(ft_envp, mini);
		return (1);
	}
	node->key = ft_strdup(current->key);
	if (node->key == NULL) 
	{
		free(node);
		copy_env_node_error(ft_envp, mini);
		return (1);
	}
	if (current->value != NULL)
	{
		node->value = ft_strdup(current->value);
		if (node->value == NULL)
		{
			free(node->key);
			free(node);
			copy_env_node_error(ft_envp, mini);
			return (1);
		}
	}
	else
		node->value = NULL;
	node->next = NULL;
	if (!(*ft_envp))
		*ft_envp = node;
	else
	{
		last = find_last(ft_envp);
		last->next = node;
	}
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
		if (copy_env_node(current, ft_envp, mini) == 1)
			return (NULL);
		current = current->next;
	}
	return (ft_envp);
}

void	replace_env(t_env_node *env_to_replace, char *arg)
{
	int	equal_index;
	int	err_code;

	err_code = 0;
	equal_index = find_equal(arg);
	free(env_to_replace->key);
	free(env_to_replace->value);
	if (equal_index > 0)
	{
		env_to_replace->key = get_key(arg, &err_code);
		env_to_replace->value = get_value(arg, &err_code);
	}
	else
	{
		env_to_replace->key = ft_strdup(arg);
		//if (env_to_replace->key == NULL)
		env_to_replace->value = NULL;
	}
}
