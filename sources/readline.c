/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:27:15 by aroullea          #+#    #+#             */
/*   Updated: 2025/03/11 14:38:59 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	line_read(void)
{
	char	*input;

	while (1)
	{
		input = readline("> ");
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
}
