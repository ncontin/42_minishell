/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:27:15 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/24 23:41:28 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_user_input(t_mini *mini)
{
	add_history(mini->input);
	mini->cmds = parsing(mini);
	if (mini->cmds == NULL)
	{
		if (mini->tokens != NULL)
		{
			free_token_argument(mini->tokens);
			free_token(mini->tokens);
			free_exit(mini);
		}
	}
	else
	{
		executor(mini, mini->cmds, -1, 0);
		free_commands(mini->cmds);
		mini->cmds = NULL;
		mini->tokens = NULL;
		free(mini->input);
		mini->input = NULL;
	}
}

void	line_read(t_mini *mini)
{
	while (1)
	{
		handle_signals();
		mini->input = readline("minishell> ");
		g_signal_received = 0;
		if (!mini->input)
		{
			if (!mini->cmds)
				ft_exit(mini, NULL);
			else
				ft_exit(mini, mini->cmds->argv);
		}
		if (ft_strlen(mini->input) > 0)
			handle_user_input(mini);
		else
		{
			free(mini->input);
			mini->input = NULL;
		}
	}
}
