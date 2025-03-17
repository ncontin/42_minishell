/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:50:03 by ncontin           #+#    #+#             */
/*   Updated: 2025/03/17 17:04:09 by ncontin          ###   ########.fr       */
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

void	execute_builtin(char **args)
{
	if (ft_strncmp(args[0], "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strncmp(args[0], "echo", 4) == 0)
	{
		ft_echo(args);
		// with options -n
	}
	else if (ft_strncmp(args[0], "exit", 4) == 0)
	{
		// no options
	}
	else if (ft_strncmp(args[0], "cd", 2) == 0)
	{
		// only relative or absolute path
	}
	else if (ft_strncmp(args[0], "env", 3) == 0)
	{
		// no options
	}
	else if (ft_strncmp(args[0], "export", 6) == 0)
	{
		// no options
	}
	else if (ft_strncmp(args[0], "unset", 5) == 0)
	{
		// no options
	}
}
