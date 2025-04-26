/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:20:38 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/26 05:16:31 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	copy_env(t_env_node **ft_envp, char *env, t_mini *mini)
{
	t_env_node	*node;
	t_env_node	*last;
	int			err_code;

	node = malloc(sizeof(t_env_node));
	if (!node)
	{
		write(STDERR_FILENO, "Memory allocation failed in copy_env\n", 37);
		free_array(mini->lst_env->path);
		free(mini->lst_env);
		free_stack(ft_envp);
		exit (EXIT_FAILURE);
	}
	node->key = get_key(env, &err_code);
	if (err_code == 1)
	{
		free(node);
		free_array(mini->lst_env->path);
		free(mini->lst_env);
		free_stack(ft_envp);
		exit (EXIT_FAILURE);
	}
	node->value = get_value(env, &err_code);
	if (err_code == 1)
	{
		free(node->key);
		free(node);
		free_array(mini->lst_env->path);
		free(mini->lst_env);
		free_stack(ft_envp);
		exit (EXIT_FAILURE);
	}
	node->next = NULL;
	if (!(*ft_envp))
		*ft_envp = node;
	else
	{
		last = find_last(ft_envp);
		last->next = node;
	}
}

t_env_node	**convert_envp_to_list(char **envp, t_mini *mini)
{
	t_env_node	**ft_envp;
	int			i;

	ft_envp = malloc(sizeof(t_env_node *));
	if (!ft_envp)
	{
		write(STDERR_FILENO, "Memory allocation failed in envp_to_list\n", 41);
		free_array(mini->lst_env->path);
		free(mini->lst_env);
		exit(EXIT_FAILURE);
	}
	*ft_envp = NULL;
	i = 0;
	while (envp[i])
	{
		copy_env(ft_envp, envp[i], mini);
		i++;
	}
	return (ft_envp);
}

void	init_envp(t_mini *mini)
{
	if (!mini)
		return ;
	mini->lst_env->envp_cp = convert_envp_to_list(mini->lst_env->envp, mini);
}
