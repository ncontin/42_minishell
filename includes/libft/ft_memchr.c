/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:39:39 by aroullea          #+#    #+#             */
/*   Updated: 2024/10/21 08:11:36 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	letter;

	i = 0;
	letter = c;
	str = (unsigned char *)s;
	while (i < n)
	{
		if (*str == letter)
			return (str);
		str++;
		i++;
	}
	return (NULL);
}
