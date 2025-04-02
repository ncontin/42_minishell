/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:27:15 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/02 10:18:54 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	line_read(t_mini *mini)
{
	while (1)
	{
		mini->input = readline("minishell> ");
		if (ft_strlen(mini->input) > 0)
		{
			add_history(mini->input);
			parsing(mini);
			if (mini->cmds != NULL)
				executor(mini);
			free_input(mini);
		}
		else
		{
			free(mini->input);
			mini->input = NULL;
		}
	}
	rl_clear_history();
}
