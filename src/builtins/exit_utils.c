/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:48:48 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/15 15:36:40 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long	ft_atoll(const char *nptr, int *overflow)
{
	int			i;
	int			sign;
	long long	result;
	int			digit;

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
		digit = nptr[i] - '0';
		if (sign == 1)
		{
			if (result >= LLONG_MAX / 10 && digit > 7)
			{
				*overflow = 1;
				return (LLONG_MAX);
			}
			if ((unsigned long long)result >= ULLONG_MAX / 10 && digit >= 5)
			{
				*overflow = 1;
				return (LLONG_MAX);
			}
		}
		else
		{
			if (result >= LLONG_MAX / 10 && digit > 8)
			{
				*overflow = 1;
				return (LLONG_MIN);
			}
			if ((unsigned long long)result >= ULLONG_MAX / 10 && digit >= 6)
			{
				*overflow = 1;
				return (LLONG_MIN);
			}
		}
		result = (result * 10) + digit;
		i++;
	}
	return (result *= sign);
}
