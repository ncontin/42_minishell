/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:51:21 by aroullea          #+#    #+#             */
/*   Updated: 2025/03/19 11:49:27 by aroullea         ###   ########.fr       */
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
		if (is_builtin(res[i]))
			execute_builtin(lst_env, res);
		//printf("%s\n", res[i]);
		i++;
	}
	free_array(res);
}
