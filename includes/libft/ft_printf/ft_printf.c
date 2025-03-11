/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:07:49 by aroullea          #+#    #+#             */
/*   Updated: 2024/10/25 16:02:33 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_check_count(va_list args, const char *str, size_t i)
{
	int	count;

	count = 0;
	if (str[i] == '%' && str[i + 1] == 'c')
		count = ft_char(args);
	else if (str[i] == '%' && str[i + 1] == 's')
		count = ft_ptrchar(args);
	else if (str[i] == '%' && str[i + 1] == 'p')
		count = ft_adr(args);
	else if (str[i] == '%' && ((str[i + 1] == 'd') || (str[i + 1] == 'i')))
		count = ft_int(args);
	else if (str[i] == '%' && str[i + 1] == 'u')
		count = ft_unsigned(args);
	else if (str[i] == '%' && str[i + 1] == 'x')
		count = ft_lowhex(args);
	else if (str[i] == '%' && str[i + 1] == 'X')
		count = ft_upperhex(args);
	return (count);
}

int	ft_add_2(const char *str, int i)
{
	int	k;

	k = 0;
	if (str[i] == '%' && str[i + 1] == 'c')
		k = 1;
	else if (str[i] == '%' && str[i + 1] == 's')
		k = 1;
	else if (str[i] == '%' && str[i + 1] == 'p')
		k = 1;
	else if (str[i] == '%' && str[i + 1] == 'd')
		k = 1;
	else if (str[i] == '%' && str[i + 1] == 'i')
		k = 1;
	else if (str[i] == '%' && str[i + 1] == 'u')
		k = 1;
	else if (str[i] == '%' && str[i + 1] == 'x')
		k = 1;
	else if (str[i] == '%' && str[i + 1] == 'X')
		k = 1;
	return (k);
}

int	ft_check_tot(const char *str, size_t *j, int tot)
{
	int	i;

	i = (*j);
	if (str[i] == '%' && str[i + 1] == '%')
	{
		write(1, "%", 1);
		i++;
		tot++;
	}
	else
	{
		write(1, &str[i], sizeof(char));
		tot++;
	}
	(*j) = i;
	return (tot);
}

int	ft_printf(const char *str, ...)
{
	va_list		args;
	size_t		i;
	int			count;
	int			tot;
	int			check;

	i = 0;
	tot = 0;
	va_start(args, str);
	while ((str[i]) && (i < ft_strlen(str)))
	{
		count = ft_check_count(args, str, i);
		check = ft_add_2(str, i);
		if (i < ft_strlen(str) && (!check))
			tot = ft_check_tot(str, &i, tot);
		tot = count + tot;
		if (check)
			i = i + 2;
		else
			i++;
		check = 0;
	}
	va_end(args);
	return (tot);
}
