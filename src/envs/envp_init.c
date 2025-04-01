/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:20:38 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/01 18:38:17 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	copy_env(t_env_node **ft_envp, char *env)
{
	t_env_node	*node;
	t_env_node	*last;

	node = malloc(sizeof(t_env_node));
	if (!node)
		return ;
	node->key = get_key(env);
	node->value = get_value(env);
	node->next = NULL;
	if (!(*ft_envp))
		*ft_envp = node;
	else
	{
		last = find_last(ft_envp);
		last->next = node;
	}
}

t_env_node	**convert_envp_to_list(char **envp)
{
	t_env_node	**ft_envp;
	int			i;

	ft_envp = malloc(sizeof(t_env_node *));
	if (!ft_envp)
		return (NULL);
	*ft_envp = NULL;
	i = 0;
	while (envp[i])
	{
		copy_env(ft_envp, envp[i]);
		i++;
	}
	return (ft_envp);
}

int	find_list_size(t_mini *mini)
{
	t_env_node	*current;
	int			envp_cp_size;

	envp_cp_size = 0;
	current = *mini->lst_env->envp_cp;
	while (current)
	{
		envp_cp_size++;
		current = current->next;
	}
	return (envp_cp_size);
}

char	**convert_envp_cp_to_array(t_mini *mini)
{
	int			envp_cp_size;
	t_env_node	*current;
	char		**envp_array;
	int			i;

	envp_cp_size = find_list_size(mini);
	i = 0;
	envp_array = malloc((envp_cp_size + 1) * sizeof(char *));
	if (!envp_array)
		return (NULL);
	current = *mini->lst_env->envp_cp;
	while (i < envp_cp_size && current)
	{
		envp_array[i] = ft_strjoin(current->key, current->value);
		if (!envp_array[i])
		{
			while (i-- > 0)
				free(envp_array[i]);
			free(envp_array);
			return (NULL);
		}
		current = current->next;
		i++;
	}
	envp_array[i] = NULL;
	return (envp_array);
}

void	init_envp(t_mini *mini)
{
	char	**envp_array;
	int		size;
	int		i;

	i = 0;
	mini->lst_env->envp_cp = convert_envp_to_list(mini->lst_env->envp);
	size = find_list_size(mini);
	envp_array = convert_envp_cp_to_array(mini);
	while (i < size)
	{
		printf("%s\n", envp_array[i]);
		i++;
	}
	free_array(envp_array);
}
