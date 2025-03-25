/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:27:15 by aroullea          #+#    #+#             */
/*   Updated: 2025/03/25 18:27:37 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	line_read(t_mini *mini)
{
	
	while (1)
	{
		mini->input = readline("minishell> ");
		if (mini->input && (ft_strlen(mini->input) > 0))
		{
			if (ft_strncmp("exit", mini->input, ft_strlen(mini->input)) == 0)
			{
				free(mini->input);
				break ;
			}
			parsing(mini);
			add_history(mini->input);
			free(mini->input);
		}
	}
	rl_clear_history();
}
