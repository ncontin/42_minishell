/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:45:45 by aroullea          #+#    #+#             */
/*   Updated: 2024/10/11 16:04:12 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*str;
	char	letter;

	i = 0;
	letter = c;
	str = (char *)s;
	while (i < ft_strlen(str)+1)
	{
		if (str[i] == letter)
			return (&str[i]);
		i++;
	}
	return (0);
}
