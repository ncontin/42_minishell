/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 09:28:52 by aroullea          #+#    #+#             */
/*   Updated: 2024/10/13 09:22:38 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len_dst;
	size_t	len_src;

	i = 0;
	len_dst = 0;
	len_src = 0;
	if (dst != NULL)
		len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	if (size != 0 && (size > len_dst))
	{
		while ((i < size - len_dst - 1) && (src[i] != '\0'))
		{
			dst[len_dst + i] = src[i];
			i++;
		}
		dst[i + len_dst] = '\0';
		return (len_dst + len_src);
	}
	return (len_src + size);
}
