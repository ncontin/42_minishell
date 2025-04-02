/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:50:03 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/02 15:45:37 by aroullea         ###   ########.fr       */
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

void	execute_builtin(t_mini *mini, char **argv)
{
	if (ft_strncmp(argv[0], "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strncmp(argv[0], "echo", 4) == 0)
		ft_echo(argv);
	else if (ft_strncmp(argv[0], "exit", 4) == 0)
		ft_exit(mini);
	else if (ft_strncmp(argv[0], "cd", 2) == 0)
		ft_cd(argv[1], mini->lst_env);
	else if (ft_strncmp(argv[0], "env", 3) == 0)
		ft_env(mini->lst_env);
	else if (ft_strncmp(argv[0], "export", 6) == 0)
		ft_export(mini->lst_env, argv);
	else if (ft_strncmp(argv[0], "unset", 5) == 0)
		ft_unset(mini->lst_env, argv);
}
