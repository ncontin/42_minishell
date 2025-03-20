/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:51:21 by aroullea          #+#    #+#             */
/*   Updated: 2025/03/20 17:07:02 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(t_env *lst_env, char *input)
{
	char	**tokens;
	int		i;

	(void)lst_env;
	i = 0;
	tokens = arg_split(input);
	tokens = unquotes(tokens);
	if (tokens != NULL)
	{
		while (tokens[i] != NULL)
		{
			if (is_builtin(tokens[i]))
				execute_builtin(lst_env, tokens);
			//printf("%s\n", token[i]);
			i++;
		}
		free_array(tokens);
	}
}
