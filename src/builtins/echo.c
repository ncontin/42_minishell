/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:55:59 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/29 15:02:38 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	display_echo(char **args, int i)
{
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
}

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
	display_echo(cmd_args, i);
	if (newline == 1)
		printf("\n");
	*exit_code = 0;
}
