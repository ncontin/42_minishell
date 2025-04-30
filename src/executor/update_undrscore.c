/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_undrscore.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:00:28 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/30 19:19:36 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_last_argument(char **args)
{
	int	i;

	i = 0;
	if (args == NULL || args[0] == NULL)
		return (0);
	while (args[i] != NULL)
		i++;
	i--;
	return (i);
}

static void	replace_underscore(char *arg, t_env_node *current)
{
	char	*tmp;

	tmp = ft_strdup(arg);
	if (tmp == NULL)
	{
		free(current->value);
		current->value = NULL;
		return ;
	}
	free(current->value);
	current->value = tmp;
	return ;
}

void	update_underscore(t_command *cmd, t_env_node **envp_cp, t_mini *mini)
{
	t_env_node	*current;
	int			i;

	current = *envp_cp;
	i = find_last_argument(cmd->argv);
	while (current != NULL)
	{
		if (ft_strncmp(current->key, "_", ft_strlen(current->key) + 1) == 0)
		{
			if (cmd->argv == NULL || cmd->argv[i] == NULL)
			{
				free(current->value);
				current->value = NULL;
				return ;
			}
			replace_underscore(cmd->argv[i], current);
			return ;
		}
		if (current->next == NULL)
		{
			if (add_export_env(mini->lst_env, "_", mini) == 1)
				return ;
		}
		current = current->next;
	}
}
