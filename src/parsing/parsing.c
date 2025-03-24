/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:51:21 by aroullea          #+#    #+#             */
/*   Updated: 2025/03/24 16:58:48 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(t_env *lst_env, char *input)
{
	char	**res;

	// int		i;
	// i = 0;
	res = arg_split(input);
	if (is_builtin(res[0]))
		execute_builtin(lst_env, res);
	// while (res[i] != NULL)
	// {
	// 	// printf("%s\n", res[i]);
	// 	i++;
	// }
	free_array(res);
}
