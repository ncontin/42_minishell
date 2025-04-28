/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:52:00 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/28 12:49:33 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env_node	*check_existing_env(t_env *lst_env, char *arg)
{
	t_env_node	*current;
	int			equal_index;

	current = *lst_env->envp_cp;
	equal_index = find_equal(arg);
	if (equal_index < 0)
		equal_index = ft_strlen(arg);
	else if (arg[equal_index - 1] == '+')
		equal_index -= 1;
	while (current)
	{
		if (ft_strncmp(arg, current->key, equal_index) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

static int	add_export_env(t_env *lst_env, char *arg)
{
	t_env_node	*env;
	t_env_node	*last;
	int			err_code;

	err_code = 0;
	env = malloc(sizeof(t_env_node));
	if (!env)
	{
		write(STDERR_FILENO, "memory allocation failed in export\n", 34);
		return (1);
	}
	if (find_equal(arg) > 0)
	{
		env->key = get_key(arg, &err_code);
		if (err_code == 1)
		{
			free(env);
			write(STDERR_FILENO, "memory allocation failed in export\n", 34);
			return (1);
		}
		env->value = get_value(arg, &err_code);
		if (err_code == 1)
		{
			free(env->key);
			free(env);
			write(STDERR_FILENO, "memory allocation failed in export\n", 34);
			return (1);
		}
	}
	else
	{
		env->key = ft_strdup(arg);
		if (env->key == NULL)
		{
			free(env);
			write(STDERR_FILENO, "memory allocation failed in export\n", 34);
			return (1);
		}
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
	return (0);
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

static void	print_id_error(t_mini *mini, char *arg)
{
	mini->exit_code = 1;
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

static int	is_valid_option(t_mini *mini, char **cmd_args)
{
	if (!cmd_args[1] || !cmd_args[1][0])
		return (0);
	if (ft_strncmp(cmd_args[1], "--", 2) == 0 && cmd_args[1][2])
	{
		ft_putstr_fd("minishell: export: ", 2);
		ft_putstr_fd(mini->cmds->argv[1], 2);
		ft_putstr_fd(": invalid option\n", 2);
		ft_putstr_fd("export: usage: export [name[=value]\n", 2);
		mini->exit_code = 2;
		return (0);
	}
	return (1);
}

static int	is_valid_identifier(t_mini *mini, char *arg)
{
	int	i;
	int	equal_index;

	if (!arg || !arg[0])
		return (0);
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
	{
		print_id_error(mini, arg);
		return (0);
	}
	equal_index = find_equal(arg);
	if (equal_index < 0)
		equal_index = ft_strlen(arg);
	if (arg[equal_index - 1] == '+')
		equal_index -= 1;
	i = 0;
	while (++i < equal_index)
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			print_id_error(mini, arg);
			return (0);
		}
	}
	return (1);
}

static int	join_env_value(t_env_node *env_to_replace, char *arg)
{
	char	*temp;
	char	*str_to_join;
	char	*tmp_value;
	int		err_code;

	err_code = 0;
	str_to_join = get_value(arg, &err_code);
	if (err_code == 1)
	{
		write(STDERR_FILENO, "memory allocation failed in export\n", 34);
		return (1);
	}
	temp = ft_strdup(env_to_replace->value);
	if (temp == NULL)
	{
		write(STDERR_FILENO, "memory allocation failed in export\n", 34);
		free(str_to_join);
		return (1);
	}
	tmp_value = ft_strjoin(temp, str_to_join);
	if (tmp_value == NULL)
	{
		write(STDERR_FILENO, "memory allocation failed in export\n", 34);
		free(str_to_join);
		free(temp);
		return (1);
	}
	free(env_to_replace->value);
	env_to_replace->value = tmp_value;
	free(temp);
	free(str_to_join);
	return (0);
}

void	ft_export(t_mini *mini, char **cmd_args)
{
	int			i;
	t_env_node	*env_to_replace;
	int			equal_index;

	i = 0;
	if (!mini->lst_env || !mini->cmds || !cmd_args[0])
		return ;
	if (cmd_args[1] && !is_valid_option(mini, cmd_args))
		return ;
	mini->lst_env->sorted_envp_cp = copy_envp_list(mini->lst_env->envp_cp, mini);
	if (!mini->lst_env->sorted_envp_cp)
		return ;
	sort_env(mini->lst_env->sorted_envp_cp);
	if (cmd_args[0])
		print_export(mini->lst_env->sorted_envp_cp, cmd_args);
	if (cmd_args[0] && cmd_args[1])
	{
		while (cmd_args[++i])
		{
			if (cmd_args[i] && !is_valid_identifier(mini, cmd_args[i]))
				continue ;
			env_to_replace = check_existing_env(mini->lst_env, cmd_args[i]);
			equal_index = find_equal(cmd_args[i]);
			if (equal_index < 0)
				equal_index = ft_strlen(cmd_args[i]);
			if (env_to_replace && cmd_args[i][equal_index - 1] != '+')
			{
				if (replace_env(env_to_replace, cmd_args[i]) == 1)
					return ;
			}
			else if (env_to_replace && cmd_args[i][equal_index - 1] == '+')
			{
				if (join_env_value(env_to_replace, cmd_args[i]) == 1)
					return ;
			}
			else
				add_export_env(mini->lst_env, cmd_args[i]);
		}
	}
	free_stack(mini->lst_env->sorted_envp_cp);
}
