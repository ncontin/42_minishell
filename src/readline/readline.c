/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:27:15 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/13 19:43:04 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	line_read(t_mini *mini)
{
	while (1)
	{
		handle_signals();
		mini->input = readline("minishell> ");
		signal_received = 0;
		if (!mini->input)
		{
			if (isatty(STDIN_FILENO))
				write(2, "exit\n", 6);
			if (!mini->cmds)
				ft_exit(mini, NULL);
			else
				ft_exit(mini, mini->cmds->argv);
		}
		if (ft_strlen(mini->input) > 0)
		{
			add_history(mini->input);
			mini->cmds = parsing(mini);
			if (mini->cmds != NULL)
				executor(mini);
			free_commands(mini->cmds);
			mini->cmds = NULL;
			mini->cmds = NULL;
			free(mini->input);
			mini->input = NULL;
		}
		else
		{
			free(mini->input);
			mini->input = NULL;
		}
	}
}
