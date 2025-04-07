/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:52:00 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/07 17:48:20 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env_node	*check_existing_env(t_env *lst_env, char *arg)
{
	t_env_node	*current;

	current = *lst_env->envp_cp;
	while (current)
	{
		if (ft_strncmp(arg, current->key, ft_strlen(arg)) == 0)
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
static void	print_id_error(t_mini *mini, char **cmd_args)
{
	mini->exit_code = 1;
	ft_putstr_fd("minishell: export: ", 2);
	ft_putstr_fd(cmd_args[1], 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
}
static int	is_valid_identifier(t_mini *mini, char **cmd_args)
{
	int	i;
	int	equal_index;

	if (!cmd_args[1] || !cmd_args[1][0])
		return (0);
	if (!ft_isalpha(cmd_args[1][0]) && cmd_args[1][0] != '_')
	{
		print_id_error(mini, cmd_args);
		return (0);
	}
	i = 1;
	equal_index = find_equal(cmd_args[1]);
	if (equal_index < 0)
		equal_index = ft_strlen(cmd_args[1]);
	while (i < equal_index)
	{
		if (!ft_isalnum(cmd_args[1][i]) && cmd_args[1][i] != '_')
		{
			print_id_error(mini, cmd_args);
			return (0);
		}
		i++;
	}
	return (1);
}

void	ft_export(t_mini *mini, char **cmd_args)
{
	int			i;
	t_env_node	*env_to_replace;

	i = 0;
	if (!mini->lst_env || !mini->cmds || !cmd_args[0])
		return ;
	if (cmd_args[1] && !is_valid_identifier(mini, cmd_args))
		return ;
	mini->lst_env->sorted_envp_cp = copy_envp_list(mini->lst_env->envp_cp);
	if (!mini->lst_env->sorted_envp_cp)
		return ;
	sort_env(mini->lst_env->sorted_envp_cp);
	if (cmd_args[0])
		print_export(mini->lst_env->sorted_envp_cp, cmd_args);
	if (cmd_args[0] && cmd_args[1])
	{
		while (cmd_args[++i])
		{
			env_to_replace = check_existing_env(mini->lst_env, cmd_args[i]);
			if (env_to_replace != NULL)
				replace_env(env_to_replace, cmd_args[i]);
			else
				add_export_env(mini->lst_env, cmd_args[i]);
		}
	}
	free_stack(mini->lst_env->sorted_envp_cp);
}
