/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:01:48 by ncontin           #+#    #+#             */
/*   Updated: 2025/05/03 12:11:08 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_options(t_mini *mini)
{
	if (!mini->cmds->argv[1])
		return (0);
	if (mini->cmds->argv[1][0] == '-' && mini->cmds->argv[1][1])
	{
		ft_putstr_fd("minishell: unset: ’", 2);
		ft_putstr_fd(mini->cmds->argv[1], 2);
		ft_putstr_fd("’: invalid option\n", 2);
		return (1);
	}
	return (0);
}

static void	del_env(t_env *current, t_env *prev, t_env **envp_stack)
{
	if (prev == NULL)
		*envp_stack = current->next;
	else
		prev->next = current->next;
	if (current->key)
		free(current->key);
	if (current->value)
		free(current->value);
	free(current);
}

static void	unset_env(t_env *env_stack, char *arg)
{
	t_env	*current;
	t_env	*prev;
	t_env	*next;

	current = env_stack;
	prev = NULL;
	while (current)
	{
		if (ft_strncmp(arg, current->key, ft_strlen(current->key) + 1) == 0)
		{
			next = current->next;
			del_env(current, prev, &env_stack);
			current = next;
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
}

void	ft_unset(t_mini *mini, char **cmd_args)
{
	int	i;

	if (check_options(mini) == 1)
	{
		mini->exit_code = 2;
		return ;
	}
	if (mini->envp_cp == NULL)
		return ;
	i = 1;
	mini->exit_code = 0;
	while (cmd_args[i])
	{
		unset_env(mini->envp_cp, cmd_args[i]);
		i++;
	}
}
