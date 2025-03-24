/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:01:48 by ncontin           #+#    #+#             */
/*   Updated: 2025/03/24 13:00:57 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	unset_env(t_env_node *current, t_env_node *prev, char *input,
		t_env_node **envp_cp)
{
	if (ft_strncmp(input, current->key, ft_strlen(current->key)) == 0)
	{
		if (prev == NULL)
			*envp_cp = current->next;
		else
			prev->next = current->next;
		if (current->key)
			free(current->key);
		if (current->value)
			free(current->value);
		free(current);
		return (1);
	}
	return (0);
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
			if (unset_env(current, prev, args[i], lst_env->envp_cp))
				current = current->next;
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
				if (unset_env(current, prev, args[i], lst_env->envp_export))
					current = current->next;
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
