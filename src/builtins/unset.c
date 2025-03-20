/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:01:48 by ncontin           #+#    #+#             */
/*   Updated: 2025/03/20 10:30:49 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	ft_unset(char **envp, char *input)
{
	int		i;
	char	*substr;
	char	*temp;

	i = 0;
	while (envp[i])
	{
		substr = ft_substr(envp[i], 0, find_equal(envp[i]));
		if (ft_strncmp(input, substr, ft_strlen(input)) == 0)
		{
			while (envp[i] && envp[i + 1])
			{
				temp = envp[i];
				envp[i] = envp[i + 1];
				envp[i + 1] = temp;
				i++;
			}
			envp[i] = NULL;
		}
		free(substr);
		i++;
	}
}
