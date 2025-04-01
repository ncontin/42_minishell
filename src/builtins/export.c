/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:52:00 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/01 15:02:39 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env_node	*check_existing_env(t_env *lst_env, char *arg)
{
	t_env_node	*current;

	current = *lst_env->envp_cp;
	while (current)
	{
		if (ft_strncmp(arg, current->key, ft_strlen(current->key)) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

// chained list
static void	add_export_env(t_env *lst_env, char *arg)
{
	t_env_node	*env;
	t_env_node	*last;

	env = malloc(sizeof(t_env_node));
	if (!env)
		return ;
	if (find_equal(arg) > 0)
	{
		env->key = get_key(arg);
		env->value = get_value(arg);
	}
	else
	{
		env->key = ft_strdup(arg);
		env->value = NULL;
	}
	env->next = NULL;
	if (!(*lst_env->envp_cp))
		*lst_env->envp_cp = env;
	else
	{
		last = find_last(lst_env->envp_cp);
		last->next = env;
	}
}

static void	swap_nodes(t_env_node *current, t_env_node *temp)
{
	char	*temp_key;
	char	*temp_value;

	if (ft_strncmp(current->key, temp->key, find_min_len(current->key,
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

void	ft_export(t_mini *mini)
{
	int			i;
	t_env_node	*env_to_replace;

	i = 0;
	if (!mini->lst_env || !mini->args || !mini->args[0])
		return ;
	mini->lst_env->sorted_envp_cp = copy_envp_list(mini->lst_env->envp_cp);
	if (!mini->lst_env->sorted_envp_cp)
		return ;
	sort_env(mini->lst_env->sorted_envp_cp);
	if (mini->args[0])
		print_export(mini->lst_env->sorted_envp_cp, mini->args);
	if (mini->args[0] && mini->args[1])
	{
		while (mini->args[++i])
		{
			env_to_replace = check_existing_env(mini->lst_env, mini->args[i]);
			if (env_to_replace != NULL)
				replace_env(env_to_replace, mini->args[i]);
			else
				add_export_env(mini->lst_env, mini->args[i]);
		}
	}
	free_stack(mini->lst_env->sorted_envp_cp);
}
