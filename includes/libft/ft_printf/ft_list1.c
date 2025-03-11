/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:08:42 by aroullea          #+#    #+#             */
/*   Updated: 2024/10/25 15:09:07 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_char(va_list args)
{
	char	c;

	c = (char) va_arg(args, int);
	write(1, &c, sizeof(char));
	return (1);
}

int	ft_ptrchar(va_list args)
{
	char	*dst;

	dst = (char *) va_arg(args, char *);
	if (!dst)
	{
		write(1, "(null)", 6);
		return (6);
	}
	else
		ft_putstr_fd(dst, 1);
	return (ft_strlen(dst));
}

int	ft_adr(va_list args)
{
	unsigned long int	res;
	int					count;

	res = (unsigned long int) va_arg(args, void *);
	if (!res)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	else
	{
		write(1, "0x", 2);
		count = ft_puthex(res, 1);
	}
	return (count + 2);
}

int	ft_int(va_list args)
{
	int	res;

	res = (int) va_arg(args, int);
	ft_putnbr_fd(res, 1);
	if (res == 0)
		return (1);
	return (ft_size(res));
}

int	ft_unsigned(va_list args)
{
	unsigned int	res;
	int				count;

	res = (unsigned int) va_arg(args, unsigned int);
	count = ft_unsigned_nbr(res);
	return (count);
}
