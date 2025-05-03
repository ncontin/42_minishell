/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 04:47:01 by aroullea          #+#    #+#             */
/*   Updated: 2025/05/03 12:15:45 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	export_checks(t_mini *mini, char **cmd_args)
{
	if (!mini->envp_cp || !mini->cmds || !cmd_args[0])
		return (1);
	if (cmd_args[1] && !is_valid_option(mini, cmd_args))
		return (1);
	return (0);
}

static int	prepare_export_env(t_mini *mini)
{
	t_env	*envp_copy;

	envp_copy = copy_envp_list(mini->envp_cp, mini);
	if (!envp_copy)
	{
		mini->sorted_envp_cp = NULL;
		return (1);
	}
	else
		mini->sorted_envp_cp = envp_copy;
	sort_env(mini->sorted_envp_cp);
	return (0);
}

static void	process_export(t_mini *mini, char **cmd_args, int i)
{
	t_env	*env_to_replace;
	int		equal_index;

	while (cmd_args[++i])
	{
		if (cmd_args[i] && !is_valid_identifier(mini, cmd_args[i]))
			continue ;
		env_to_replace = check_existing_env(mini->envp_cp, cmd_args[i]);
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
			if (join_env_value(env_to_replace, cmd_args[i], mini) == 1)
				return ;
		}
		else
			if (add_export_env(mini->envp_cp, cmd_args[i], mini) == 1)
				return ;
	}
}

void	ft_export(t_mini *mini, char **cmd_args)
{
	if (export_checks(mini, cmd_args) == 1)
		return ;
	if (prepare_export_env(mini) == 1)
		return ;
	if (cmd_args[0] && !cmd_args[1])
		print_export(mini->sorted_envp_cp);
	else if (cmd_args[0] && cmd_args[1])
		process_export(mini, cmd_args, 0);
	free_stack(mini->sorted_envp_cp);
}
