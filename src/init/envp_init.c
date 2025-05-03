/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:20:38 by ncontin           #+#    #+#             */
/*   Updated: 2025/05/03 12:22:28 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*new_env_node(char *env, t_env *head)
{
	int		err_code;
	t_env	*node;

	err_code = 0;
	node = malloc(sizeof(t_env));
	if (!node)
	{
		write(STDERR_FILENO, "Memory allocation failed in copy_env\n", 37);
		copy_env_error(head);
	}
	node->key = get_key(env, &err_code);
	if (err_code == 1)
	{
		free(node);
		copy_env_error(head);
	}
	node->value = get_value(env, &err_code);
	if (err_code == 1)
	{
		free(node->key);
		free(node);
		copy_env_error(head);
	}
	node->next = NULL;
	return (node);
}

static void	append_env_node(t_env **head, t_env **new, t_env **end)
{
	if (*head == NULL)
	{
		*head = *new;
		*end = *new;
	}
	else
	{
		(*end)->next = *new;
		*end = *new;
	}
}

static t_env	*convert_envp_to_list(char **envp)
{
	int		i;
	t_env	*new;
	t_env	*end;
	t_env	*head;

	i = 0;
	end = NULL;
	new = NULL;
	head = NULL;
	while (envp[i])
	{
		new = new_env_node(envp[i], head);
		append_env_node(&head, &new, &end);
		i++;
	}
	return (head);
}

void	init_envp(t_mini *mini, char **envp)
{
	if (!mini)
		return ;
	mini->envp_cp = convert_envp_to_list(envp);
}
