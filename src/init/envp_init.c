/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:20:38 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/26 06:40:08 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env_node	*new_env_node(char *env, t_env_node **ft_envp, t_mini *mini)
{
	int			err_code;
	t_env_node	*node;

	err_code = 0;
	node = malloc(sizeof(t_env_node));
	if (!node)
	{
		write(STDERR_FILENO, "Memory allocation failed in copy_env\n", 37);
		copy_env_error(ft_envp, mini);
	}
	node->key = get_key(env, &err_code);
	if (err_code == 1)
	{
		free(node);
		copy_env_error(ft_envp, mini);
	}
	node->value = get_value(env, &err_code);
	if (err_code == 1)
	{
		free(node->key);
		free(node);
		copy_env_error(ft_envp, mini);
	}
	node->next = NULL;
	return (node);
}

static void	append_env_node(t_env_node **ft_envp, t_env_node *node)
{
	t_env_node	*last;

	if (!(*ft_envp))
		*ft_envp = node;
	else
	{
		last = find_last(ft_envp);
		last->next = node;
	}
}

static void	copy_env(t_env_node **ft_envp, char *env, t_mini *mini)
{
	t_env_node	*node;

	node = new_env_node(env, ft_envp, mini);
	append_env_node(ft_envp, node);
}

t_env_node	**convert_envp_to_list(char **envp, t_mini *mini)
{
	t_env_node	**ft_envp;
	int			i;

	ft_envp = malloc(sizeof(t_env_node *));
	if (!ft_envp)
		envp_to_list_error(mini);
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
