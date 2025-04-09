/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:50:03 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/09 08:47:47 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *str)
{
	char	*builtins[8];
	int		i;
	size_t	len;

	builtins[0] = "pwd";
	builtins[1] = "cd";
	builtins[2] = "exit";
	builtins[3] = "env";
	builtins[4] = "export";
	builtins[5] = "unset";
	builtins[6] = "echo";
	builtins[7] = NULL;
	if (str == NULL)
		return (0);
	len = ft_strlen(str);
	if (len == 0)
		return (0);
	i = 0;
	while (builtins[i])
	{
		if (ft_strncmp(str, builtins[i], len) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	execute_builtin(t_mini *mini, char **cmd_args)
{
	if (ft_strncmp(cmd_args[0], "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strncmp(cmd_args[0], "echo", 4) == 0)
		ft_echo(cmd_args);
	else if (ft_strncmp(cmd_args[0], "exit", 4) == 0)
		ft_exit(mini, cmd_args);
	else if (ft_strncmp(cmd_args[0], "cd", 2) == 0)
		ft_cd(mini);
	else if (ft_strncmp(cmd_args[0], "env", 3) == 0)
		ft_env(mini);
	else if (ft_strncmp(cmd_args[0], "export", 6) == 0)
		ft_export(mini, cmd_args);
	else if (ft_strncmp(cmd_args[0], "unset", 5) == 0)
		ft_unset(mini, cmd_args);
}
