/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:50:03 by ncontin           #+#    #+#             */
/*   Updated: 2025/03/17 13:45:28 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *str)
{
	char	*builtins[] = {"pwd", "cd", "exit", "env", "export", "unset",
			"echo", NULL};
	int		i;

	i = 0;
	while (builtins[i])
	{
		if (ft_strncmp(str, builtins[i], ft_strlen(str)) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	execute_builtin(char *str)
{
	if (ft_strncmp(str, "pwd", 3) == 0)
	{
		// no options
		ft_pwd();
	}
	else if (ft_strncmp(str, "echo", 4))
	{
		// with options -n
	}
	else if (ft_strncmp(str, "exit", 4))
	{
		// no options
	}
	else if (ft_strncmp(str, "cd", 2) == 0)
	{
		// only relative or absolute path
	}
	else if (ft_strncmp(str, "env", 3))
	{
		// no options
	}
	else if (ft_strncmp(str, "export", 6))
	{
		// no options
	}
	else if (ft_strncmp(str, "unset", 5))
	{
		// no options
	}
}
