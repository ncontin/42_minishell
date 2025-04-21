/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:20:38 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/21 16:28:25 by aroullea         ###   ########.fr       */
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

int	find_list_size(t_env *lst_env)
{
	t_env_node	*current;
	int			envp_cp_size;

	envp_cp_size = 0;
	current = *lst_env->envp_cp;
	while (current)
	{
		envp_cp_size++;
		current = current->next;
	}
	return (envp_cp_size);
}

int	add_env_to_array(t_env_node *current, char **envp_array, int i)
{
	char	*temp;

	temp = NULL;
	temp = ft_strjoin(current->key, "=");
	if (temp == NULL)
	{
		if (envp_array != NULL)
			free_array(envp_array);
		return (1);
	}
	else if (temp != NULL && current->value == NULL)
		envp_array[i] = ft_strdup(temp);
	else if (temp != NULL && current->value != NULL)
		envp_array[i] = ft_strjoin(temp, current->value);
	free(temp);
	if (!envp_array[i])
	{
		if (envp_array != NULL)
			free_array(envp_array);
		return (1);
	}
	return (0);
}

int	get_envp_array(t_env *lst_env, char ***envp)
{
	int			envp_cp_size;
	char		**envp_array;
	t_env_node	*current;
	int			i;

	envp_array = NULL;
	envp_cp_size = find_list_size(lst_env);
	i = 0;
	envp_array = malloc((envp_cp_size + 1) * sizeof(char *));
	if (!envp_array)
		return (1);
	current = *lst_env->envp_cp;
	while (i < envp_cp_size && current)
	{
		if (add_env_to_array(current, envp_array, i) == 1)
			return (1);
		current = current->next;
		i++;
	}
	envp_array[i] = NULL;
	(*envp) = envp_array;
	return (0);
}

void	init_envp(t_mini *mini)
{
	// char	**envp_array;
	// int		size;
	// int		i;
	if (!mini)
		return ;
	mini->lst_env->envp_cp = convert_envp_to_list(mini->lst_env->envp);
	// size = find_list_size(mini->lst_env);
	// envp_array = get_envp_array(mini->lst_env);
	// while (i < size)
	// {
	// 	printf("%s\n", envp_array[i]);
	// 	i++;
	// }
	// free_array(envp_array);
}
