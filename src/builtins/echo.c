/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:55:59 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/14 08:18:47 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **cmd_args, long long int *exit_code)
{
	int	i;
	int	j;
	int	newline;

	newline = 1;
	i = 1;
	j = 2;
	while (cmd_args[i] && cmd_args[i][0] == '-' && cmd_args[i][1] == 'n')
	{
		while (cmd_args[i][j] == 'n')
			j++;
		if (cmd_args[i][2] == '\0' || cmd_args[i][j] == '\0')
		{
			newline = 0;
			i++;
			j = 2;
		}
		else
			break ;
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
