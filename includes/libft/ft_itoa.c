/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:46:25 by aroullea          #+#    #+#             */
/*   Updated: 2024/10/14 16:09:21 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_size_str(int n)
{
	int		i;

	i = 0;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char	*ft_add_number_neg(int n, int size)
{
	int		i;
	char	*str;

	i = size;
	n = n * (-1);
	str = (char *) malloc (sizeof(char) * (size + 2));
	if (str == NULL)
		return (NULL);
	str[0] = '-';
	str[i + 1] = '\0';
	while (i > 0)
	{
		str[i] = (n % 10) + 48;
		n /= 10;
		i--;
	}
	return (str);
}

static char	*ft_add_number_pos(int n, int size)
{
	int		i;
	char	*str;

	if (n == 0)
		size = 1;
	i = size;
	str = (char *) malloc (sizeof(char) * (size + 1));
	if (str == NULL)
		return (NULL);
	str[i] = '\0';
	while (i > 0)
	{
		str[i - 1] = (n % 10) + 48;
		n /= 10;
		i--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	int		size;
	char	*str;

	str = NULL;
	size = ft_size_str(n);
	if (n >= 0 && n <= 2147483647)
		str = ft_add_number_pos(n, size);
	else if (n < 0 && n >= -2147483647)
		str = ft_add_number_neg(n, size);
	else
		str = ft_strdup("-2147483648");
	return (str);
}
