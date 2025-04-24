/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:10:55 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/24 19:13:51 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	skip_whitespace(const char *nptr)
{
	int	i;

	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	return (i);
}

static int	get_sign(const char *nptr, int *i)
{
	int	sign;

	sign = 1;
	if (nptr[*i] == '+' || nptr[*i] == '-')
	{
		if (nptr[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

static int	check_overflow(long long result, int digit, int sign, int *overflow)
{
	if (sign == 1)
	{
		if (result > LLONG_MAX / 10 || (result == LLONG_MAX / 10 && digit > 7))
		{
			*overflow = 1;
			return (1);
		}
	}
	else
	{
		if (result > LLONG_MAX / 10 || (result == LLONG_MAX / 10 && digit > 8))
		{
			*overflow = 1;
			return (1);
		}
	}
	return (0);
}

long long	ft_atoll(const char *nptr, int *overflow)
{
	int			i;
	int			sign;
	long long	result;
	int			digit;

	result = 0;
	i = skip_whitespace(nptr);
	sign = get_sign(nptr, &i);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		digit = nptr[i] - '0';
		if (check_overflow(result, digit, sign, overflow))
		{
			if (sign == 1)
				return (LLONG_MAX);
			else
				return (LLONG_MIN);
		}
		result = (result * 10) + digit;
		i++;
	}
	return (result * sign);
}
