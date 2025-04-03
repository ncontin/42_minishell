/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:27:15 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/03 11:41:26 by aroullea         ###   ########.fr       */
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
			ft_exit(mini);
		}
		if (ft_strlen(mini->input) > 0)
		{
			add_history(mini->input);
			parsing(mini);
			if (mini->cmds != NULL)
				executor(mini);
			free_commands(mini->cmds);
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
