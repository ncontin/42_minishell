/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:49:08 by aroullea          #+#    #+#             */
/*   Updated: 2025/03/19 13:16:20 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dst;
	size_t	i;
	size_t	size;

	i = 0;
	size = ft_strlen(s);
	dst = (char *)malloc(size + 1);
	if (dst == NULL)
		return (NULL);
	while (i <= size)
	{
		dst[i] = s[i];
		i++;
	}
	return (dst);
}
