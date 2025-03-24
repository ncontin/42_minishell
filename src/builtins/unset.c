/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:01:48 by ncontin           #+#    #+#             */
/*   Updated: 2025/03/24 16:14:05 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unset_env(t_env_node *current, t_env_node *prev,
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

void	ft_unset(t_env *lst_env, char **args)
{
	t_env_node	*current;
	t_env_node	*prev;
	int			i;

	if (!lst_env->envp_cp)
		return ;
	i = 1;
	while (args[i])
	{
		current = *lst_env->envp_cp;
		prev = NULL;
		while (current)
		{
			if (ft_strncmp(args[i], current->key, ft_strlen(current->key)) == 0)
			{
				unset_env(current, prev, lst_env->envp_cp);
				current = current->next;
			}
			else
			{
				prev = current;
				current = current->next;
			}
		}
		if (lst_env->envp_export && *lst_env->envp_export)
		{
			current = *lst_env->envp_export;
			prev = NULL;
			while (current)
			{
				if (ft_strncmp(args[i], current->key,
						ft_strlen(current->key)) == 0)
				{
					unset_env(current, prev, lst_env->envp_export);
					current = current->next;
				}
				else
				{
					prev = current;
					current = current->next;
				}
			}
		}
		i++;
	}
}
