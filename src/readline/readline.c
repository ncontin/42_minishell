/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:27:15 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/09 11:59:58 by ncontin          ###   ########.fr       */
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
