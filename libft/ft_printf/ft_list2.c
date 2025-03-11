/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:09:38 by aroullea          #+#    #+#             */
/*   Updated: 2024/10/25 15:10:06 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_lowhex(va_list args)
{
	unsigned int	res;
	int				count;

	count = 0;
	res = (unsigned int) va_arg(args, unsigned int);
	count = ft_puthex(res, 1);
	return (count);
}

int	ft_upperhex(va_list args)
{
	unsigned int	res;
	int				count;

	count = 0;
	res = (unsigned int) va_arg(args, unsigned int);
	count = ft_puthex(res, 0);
	return (count);
}

size_t	ft_size(int n)
{
	int	i;

	i = 0;
	if (n < 0)
		i = 1;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

int	ft_puthex(unsigned long int n, int low)
{
	char	c;
	int		count;

	count = 0;
	if (n >= 16)
		count += ft_puthex(n / 16, low);
	if (((n % 16) > 9) && low)
		c = (n % 16) + 87;
	else if (((n % 16) > 9) && !low)
		c = (n % 16) + 55;
	else
		c = (n % 16) + 48;
	write(1, &c, 1);
	count++;
	return (count);
}

int	ft_unsigned_nbr(unsigned int nbr)
{
	char	c;
	int		res;
	int		count;

	count = 0;
	if (nbr >= 10)
		count += ft_unsigned_nbr(nbr / 10);
	res = nbr % 10;
	c = res + 48;
	write(1, &c, 1);
	count++;
	return (count);
}
