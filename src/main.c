/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:10:37 by aroullea          #+#    #+#             */
/*   Updated: 2025/05/03 08:58:02 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal_received = 0;

static void	init_mini(t_mini *mini)
{
	mini->args = NULL;
	mini->tokens = NULL;
	mini->cmds = NULL;
	mini->envp_cp = NULL;
	mini->sorted_envp_cp = NULL;
	mini->error = 0;
	mini->exit_code = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;

	(void)argv;
	if (argc >= 2)
	{
		write(2, "Too many arguments \n", 20);
		return (1);
	}
	init_mini(&mini);
	init_envp(&mini, envp);
	line_read(&mini);
	return (0);
}
