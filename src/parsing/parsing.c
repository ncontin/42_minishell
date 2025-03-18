/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:51:21 by aroullea          #+#    #+#             */
/*   Updated: 2025/03/17 19:00:17 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(t_env *lst_env, char *input)
{
	char	**res;
	int		i;

	(void)lst_env;
	i = 0;
	res = arg_split(input);
	while (res[i] != NULL)
	{
		if (is_builtin(res[0]))
			execute_builtin(lst_env, res);
		// printf("%s\n", res[i]);
		free(res[i]);
		i++;
	}
	free(res);
}
