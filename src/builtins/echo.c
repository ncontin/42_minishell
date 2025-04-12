/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:55:59 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/12 13:32:47 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **cmd_args, long long int *exit_code)
{
	int	i;
	int	newline;

	newline = 1;
	i = 1;
	while (cmd_args[i] && cmd_args[i][0] == '-' && cmd_args[i][1] == 'n')
	{
		newline = 0;
		i++;
	}
	while (cmd_args[i])
	{
		printf("%s", cmd_args[i]);
		if (cmd_args[i + 1])
			printf(" ");
		i++;
	}
	if (newline == 1)
		printf("\n");
	*exit_code = 0;
}
