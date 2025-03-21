/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:52:00 by ncontin           #+#    #+#             */
/*   Updated: 2025/03/21 16:39:06 by ncontin          ###   ########.fr       */
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

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst || !new)
		return ;
	else if (lst)
	{
		if (*lst)
		{
			last = *lst;
			while (last->next != NULL)
			{
				last = last->next;
			}
			last->next = new;
		}
		else
		{
			*lst = new;
		}
	}
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
			printf("key: %s\nvalue: %s\n", env->key, env->value);
		}
		else
		{
			env->key = ft_strdup(args[i]);
			env->value = ft_strdup("");
			printf("key: %s\nvalue: %s\n", env->key, env->value);
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

// static char	**add_env(char **args)
// {
// 	char	**env_added;
// 	int		i;
// 	int		args_len;

// 	args_len = 0;
// 	while (args[args_len])
// 		args_len++;
// 	env_added = malloc((args_len + 1) * sizeof(char *));
// 	if (!env_added)
// 		return (NULL);
// 	i = 0;
// 	while (args[i + 1])
// 	{
// 		env_added[i] = ft_strdup(args[i + 1]);
// 		printf("added\n");
// 		i++;
// 	}
// 	env_added[i] = NULL;
// 	return (env_added);
// }

static void	print_export(t_env_node **sorted_envp_cp, t_env_node **envp_export,
		char **args)
{
	if (args[0] && !args[1])
	{
		if (sorted_envp_cp && *sorted_envp_cp)
			print_env_stack(sorted_envp_cp);
		printf("is it?\n");
		print_env_stack(envp_export);
	}
}

// void	ft_export_node(char **args, char **envp)
// {
// 	char			**sorted_env;
// 	t_export_node	*env_stack;

// 	env_stack = NULL;
// 	sorted_env = copy_env(envp);
// 	sort_env(sorted_env);
// 	add_export(args, &env_stack);
// 	print_export(sorted_env, args, &env_stack);
// 	free_array(sorted_env);
// }

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
	lst_env->envp_export = malloc(sizeof(t_env_node *));
	if (!lst_env->envp_export)
		return ;
	*(lst_env->envp_export) = NULL; // Initialize to empty list
	// You might need to implement a function to convert env_node to char**
	lst_env->sorted_envp_cp = copy_envp_list(lst_env->envp_cp);
	if (!lst_env->sorted_envp_cp)
		return ;
	sort_env(lst_env->sorted_envp_cp);
	if (args[1])
		add_export_env(lst_env->envp_export, args);
	print_export(lst_env->sorted_envp_cp, lst_env->envp_export, args);
	free_stack(lst_env->sorted_envp_cp);
}
