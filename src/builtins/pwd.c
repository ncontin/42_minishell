/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:28:54 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/29 11:55:18 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_options(t_mini *mini)
{
	if (!mini->cmds->argv[1])
		return (0);
	if (mini->cmds->argv[1][0] == '-' && mini->cmds->argv[1][1])
	{
		ft_putstr_fd("minishell: pwd: ’", 2);
		ft_putstr_fd(mini->cmds->argv[1], 2);
		ft_putstr_fd("’: invalid option\n", 2);
		ft_putstr_fd("pwd: usage: pwd\n", 2);
		return (1);
	}
	return (0);
}

void	ft_pwd(t_mini *mini)
{
	char	*buffer;

	if (check_options(mini) == 1)
	{
		mini->exit_code = 2;
		return ;
	}
	buffer = getcwd(NULL, 0);
	if (buffer)
	{
		mini->exit_code = 0;
		printf("%s\n", buffer);
		free(buffer);
	}
	else
	{
		mini->exit_code = 1;
		perror("pwd");
	}
}
