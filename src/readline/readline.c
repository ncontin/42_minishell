/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:27:15 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/06 15:56:07 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	line_read(t_mini *mini)
{
	while (1)
	{
		mini->input = readline("minishell> ");
		if (!mini->input)
		{
			if (isatty(STDIN_FILENO))
				write(2, "exit\n", 6);
			ft_exit(mini, NULL);
		}
		if (ft_strlen(mini->input) > 0)
		{
			add_history(mini->input);
			mini->cmds = parsing(mini);
			if (mini->cmds != NULL)
				executor(mini);
			free_commands(mini->cmds);
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
