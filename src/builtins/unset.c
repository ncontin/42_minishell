/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:01:48 by ncontin           #+#    #+#             */
/*   Updated: 2025/03/25 17:46:34 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	del_env(t_env_node *current, t_env_node *prev,
		t_env_node **envp_stack)
{
	if (prev == NULL)
		*envp_stack = current->next;
	else
		prev->next = current->next;
	if (current->key)
		free(current->key);
	if (current->value)
		free(current->value);
	free(current);
}

static void	unset_env(t_env_node **env_stack, char *arg)
{
	t_env_node	*current;
	t_env_node	*prev;
	t_env_node	*next;

	current = *env_stack;
	prev = NULL;
	while (current)
	{
		if (ft_strncmp(arg, current->key, ft_strlen(current->key)) == 0)
		{
			next = current->next;
			del_env(current, prev, env_stack);
			current = next;
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
}

void	ft_unset(t_env *lst_env, char **args)
{
	int	i;

	if (!lst_env->envp_cp)
		return ;
	i = 1;
	while (args[i])
	{
		unset_env(lst_env->envp_cp, args[i]);
		if (lst_env->envp_export && *lst_env->envp_export)
			unset_env(lst_env->envp_export, args[i]);
		i++;
	}
}
