/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:27:15 by aroullea          #+#    #+#             */
/*   Updated: 2025/03/12 17:18:56 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	line_read(void)
{
	char	*input;

	while (1)
	{
		input = readline("minishell> ");
		if (input && (ft_strlen(input) > 0))
		{
			if (ft_strncmp("exit", input, ft_strlen(input)) == 0)
			{
				free(input);
				break ;
			}
			add_history(input);
			free(input);
		}
	}
	rl_clear_history();
}
