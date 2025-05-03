/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:52:00 by ncontin           #+#    #+#             */
/*   Updated: 2025/05/03 10:55:02 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*check_existing_env(t_env *envp_cp, char *arg)
{
	t_env	*current;
	int		equal_index;

	current = envp_cp;
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

void	swap_nodes(t_env *current, t_env *temp)
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

void	sort_env(t_env *envp_cp)
{
	t_env	*current;
	t_env	*temp;

	if (envp_cp == NULL)
		return ;
	current = envp_cp;
	while (current != NULL)
	{
		temp = current->next;
		while (temp != NULL)
		{
			swap_nodes(current, temp);
			temp = temp->next;
		}
		current = current->next;
	}
}

int	is_valid_option(t_mini *mini, char **cmd_args)
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

int	is_valid_identifier(t_mini *mini, char *arg)
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
