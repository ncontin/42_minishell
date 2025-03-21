/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:51:21 by aroullea          #+#    #+#             */
/*   Updated: 2025/03/21 11:39:06 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(t_env *lst_env, char *input)
{
	int		i;
	char	**tokens;
	t_token	*tokens_info;

	(void)lst_env;
	i = 0;
	tokens = arg_split(input);
	tokens_info = unquotes(tokens);
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
