/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:30:30 by aroullea          #+#    #+#             */
/*   Updated: 2024/10/11 18:44:43 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static void	ft_copy(char *destination, char *source, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*destination++ = *source++;
		i++;
	}
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*destination;
	char	*source;

	if (!dest && !src)
		return (NULL);
	destination = (char *)dest;
	source = (char *)src;
	i = 0;
	if (dest <= src)
	{
		ft_copy(destination, source, n);
	}
	else
	{
		source += (n -1);
		destination += (n -1);
		while (i < n)
		{
			*destination-- = *source--;
			i++;
		}
	}
	return (dest);
}
