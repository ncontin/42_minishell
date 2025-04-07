/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:04:18 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/07 11:49:31 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_special_vars(char *arg, t_mini *mini)
{
	char	*result;
	char	*full_string;
	char	*partial_string;

	if (ft_strncmp(arg, "$?", 2) == 0 && !arg[2])
	{
		result = ft_itoa(mini->exit_code);
		free(arg);
		return (result);
	}
	else if (ft_strncmp(arg, "$?", 2) == 0 && arg[2])
	{
		result = ft_itoa(mini->exit_code);
		partial_string = ft_substr(arg, 2, ft_strlen(arg) - 2);
		full_string = ft_strjoin(result, partial_string);
		free(arg);
		free(partial_string);
		return (full_string);
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
