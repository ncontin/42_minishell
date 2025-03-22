/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:51:21 by aroullea          #+#    #+#             */
/*   Updated: 2025/03/22 11:14:40 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(t_env *lst_env, char *input)
{
	int		i;
	char	**tokens;
	t_bool	even_quotes;

	(void)lst_env;
	i = 0;
	tokens = arg_split(input);
	if (tokens == NULL)
		return ;
	even_quotes = is_even_quotes(tokens);
	if (even_quotes == FALSE)
		return ;
	create_list(tokens);
	if (tokens != NULL)
	{
		while (tokens[i] != NULL)
		{
			/*if (is_builtin(tokens[i]))
				execute_builtin(lst_env, tokens);*/
			printf("%s\n", tokens[i]);
			i++;
		}
		free_array(tokens);
	}
}
