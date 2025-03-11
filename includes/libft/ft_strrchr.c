/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:25:31 by aroullea          #+#    #+#             */
/*   Updated: 2024/10/11 17:07:08 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	char			*str;
	unsigned char	letter;

	str = (char *)s;
	i = ft_strlen(str);
	letter = c;
	while (i >= 0)
	{
		if (str[i] == letter)
			return (&str[i]);
		i--;
	}
	return (NULL);
}
