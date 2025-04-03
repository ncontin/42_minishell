/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:48:48 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/03 13:18:37 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long	ft_atoll(const char *nptr, int *overflow)
{
	int			i;
	int			sign;
	long long	result;

	result = 0;
	sign = 1;
	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (sign == -1 && (result >= LLONG_MAX / 10 && (nptr[i] - '0') > 8))
			*overflow = 1;
		else if (sign != -1 && result >= LLONG_MAX / 10 && (nptr[i] - '0') > 7)
			*overflow = 1;
		result = (result * 10) + (nptr[i] - '0');
		i++;
	}
	return (result *= sign);
}

void	free_all(t_mini *mini)
{
	if (mini->input)
		free(mini->input);
	if (mini->cmds)
		free_commands(mini->cmds);
	if (mini->lst_env)
	{
		if (mini->lst_env->envp_cp)
			free_stack(mini->lst_env->envp_cp);
		free_path(mini->lst_env);
		free(mini->lst_env);
	}
}
