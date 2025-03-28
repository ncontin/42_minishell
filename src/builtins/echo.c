/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:55:59 by ncontin           #+#    #+#             */
/*   Updated: 2025/03/28 16:20:39 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_mini *mini)
{
	int	i;
	int	newline;

	newline = 1;
	i = 1;
	while (mini->args[i] && mini->args[i][0] == '-' && mini->args[i][1] == 'n')
	{
		newline = 0;
		i++;
	}
	while (mini->args[i])
	{
		printf("%s", mini->args[i]);
		if (mini->args[i + 1])
			printf(" ");
		i++;
	}
	if (newline == 1)
		printf("\n");
}
