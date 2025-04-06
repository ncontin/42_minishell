/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:04:18 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/06 15:32:27 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_special_vars(char *arg, t_mini *mini)
{
	char	*result;

	if (ft_strncmp(arg, "$?", 2) == 0)
	{
		result = ft_itoa(mini->exit_code);
		free(arg);
		return (result);
	}
	return (arg);
}

void	expander(t_mini *mini)
{
	int			i;
	t_command	*current;

	current = mini->cmds;
	while (current)
	{
		i = 0;
		while (current->argv && current->argv[i])
		{
			current->argv[i] = expand_special_vars(current->argv[i], mini);
			i++;
		}
		current = current->next;
	}
}
