/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:01:27 by aroullea          #+#    #+#             */
/*   Updated: 2025/05/03 11:57:36 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_list_size(t_env *envp_cp)
{
	t_env	*current;
	int		envp_cp_size;

	envp_cp_size = 0;
	current = envp_cp;
	while (current != NULL)
	{
		envp_cp_size++;
		current = current->next;
	}
	return (envp_cp_size);
}

static int	add_env_to_array(t_env *current, char **envp_array, int i)
{
	char	*temp;

	temp = NULL;
	envp_array[i] = NULL;
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
	if (envp_array[i] == NULL)
	{
		if (envp_array != NULL)
			free_array(envp_array);
		return (1);
	}
	return (0);
}

int	get_envp_array(t_env *envp_cp, char ***envp)
{
	int		envp_cp_size;
	char	**envp_array;
	t_env	*current;
	int		i;

	envp_array = NULL;
	envp_cp_size = find_list_size(envp_cp);
	i = 0;
	envp_array = (char **)malloc((envp_cp_size + 1) * sizeof(char *));
	if (envp_array == NULL)
		return (1);
	current = envp_cp;
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
