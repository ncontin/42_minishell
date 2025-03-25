/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:50:03 by ncontin           #+#    #+#             */
/*   Updated: 2025/03/25 16:01:15 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *str)
{
	char	*builtins[] = {"pwd", "cd", "exit", "env", "export", "unset",
			"echo", NULL};
	int		i;
	size_t	len;

	if (str == NULL)
		return (0);
	len = ft_strlen(str);
	i = 0;
	while (builtins[i])
	{
		if (ft_strncmp(str, builtins[i], len) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	execute_builtin(t_env *lst_env, char **args)
{
	if (ft_strncmp(args[0], "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strncmp(args[0], "echo", 4) == 0)
		ft_echo(args);
	// else if (ft_strncmp(args[0], "exit", 4) == 0)
	// {
	// 	// no options
	// }
	else if (ft_strncmp(args[0], "cd", 2) == 0)
		ft_cd(args[1]);
	else if (ft_strncmp(args[0], "env", 3) == 0)
		ft_env(lst_env);
	else if (ft_strncmp(args[0], "export", 6) == 0)
		ft_export(lst_env, args);
	else if (ft_strncmp(args[0], "unset", 5) == 0)
		ft_unset(lst_env, args);
}
