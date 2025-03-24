/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:52:00 by ncontin           #+#    #+#             */
/*   Updated: 2025/03/24 13:02:48 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_len(char *s1, char *s2)
{
	int	s1_len;
	int	s2_len;
	int	len;

	s2_len = ft_strlen(s2);
	s1_len = ft_strlen(s1);
	if (s1_len < s2_len)
		len = s1_len;
	else
		len = s2_len;
	return (len);
}

// chained list
static void	add_export_env(t_env_node **export_env_stack, char **args)
{
	t_env_node	*env;
	t_env_node	*last;
	int			i;
	int			equal_index;

	i = 1;
	while (args[i])
	{
		env = malloc(sizeof(t_env_node));
		if (!env)
			return ;
		equal_index = find_equal(args[i]);
		if (equal_index > 0)
		{
			env->key = get_key(args[i]);
			env->value = get_value(args[i]);
		}
		else
		{
			env->key = ft_strdup(args[i]);
			env->value = NULL;
		}
		env->next = NULL;
		if (!(*export_env_stack))
			*export_env_stack = env;
		else
		{
			last = find_last(export_env_stack);
			last->next = env;
		}
		i++;
	}
}

static void	print_export(t_env_node **sorted_envp_cp, t_env_node **envp_export,
		char **args)
{
	if (args[0] && !args[1])
	{
		if (sorted_envp_cp && *sorted_envp_cp)
			print_env_stack(sorted_envp_cp);
		if (envp_export)
			print_env_stack(envp_export);
	}
}

t_env_node	**copy_envp_list(t_env_node **envp_cp)
{
	t_env_node	**ft_envp;
	t_env_node	*node;
	t_env_node	*last;
	t_env_node	*current;

	current = *envp_cp;
	ft_envp = malloc(sizeof(t_env_node *));
	if (!ft_envp)
		return (NULL);
	*ft_envp = NULL;
	while (current)
	{
		node = malloc(sizeof(t_env_node));
		if (!node)
			return (NULL);
		node->key = ft_strdup(current->key);
		node->value = ft_strdup(current->value);
		node->next = NULL;
		if (!(*ft_envp))
			*ft_envp = node;
		else
		{
			last = find_last(ft_envp);
			last->next = node;
		}
		current = current->next;
	}
	return (ft_envp);
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
		if (ft_strncmp(min->key, current->key, find_len(min->key,
					current->key)) > 0)
			min = current;
		current = current->next;
	}
	return (min);
}

static void	swap_nodes(t_env_node *current, t_env_node *temp)
{
	char	*temp_key;
	char	*temp_value;

	if (ft_strncmp(current->key, temp->key, find_len(current->key,
				temp->key)) > 0)
	{
		temp_key = current->key;
		temp_value = current->value;
		current->key = temp->key;
		current->value = temp->value;
		temp->key = temp_key;
		temp->value = temp_value;
	}
}

static void	sort_env(t_env_node **envp_cp)
{
	t_env_node	*current;
	t_env_node	*temp;

	if (!envp_cp || !*envp_cp)
		return ;
	current = *envp_cp;
	while (current)
	{
		temp = current->next;
		while (temp)
		{
			swap_nodes(current, temp);
			temp = temp->next;
		}
		current = current->next;
	}
}

void	ft_export(t_env *lst_env, char **args)
{
	if (!lst_env || !args || !args[0])
		return ;
	// might need to implement a function to convert env_node to char**
	lst_env->sorted_envp_cp = copy_envp_list(lst_env->envp_cp);
	if (!lst_env->sorted_envp_cp)
		return ;
	sort_env(lst_env->sorted_envp_cp);
	if (args[1])
		add_export_env(lst_env->envp_export, args);
	print_export(lst_env->sorted_envp_cp, lst_env->envp_export, args);
	free_stack(lst_env->sorted_envp_cp);
}
