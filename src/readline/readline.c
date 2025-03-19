/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:27:15 by aroullea          #+#    #+#             */
/*   Updated: 2025/03/19 15:13:07 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	line_read(t_env *lst_env)
{
	char	*input;

	while (1)
	{
		input = user_input("minishell> ");
		if (input && (ft_strlen(input) > 0))
		{
			if (ft_strncmp("exit", input, 4) == 0)
			{
				free(input);
				break ;
			}
			parsing(lst_env, input);
			add_history(input);
			free(input);
		}
	}
	rl_clear_history();
}
