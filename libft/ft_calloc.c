/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 09:01:38 by aroullea          #+#    #+#             */
/*   Updated: 2025/01/18 17:40:41 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*p;
	size_t	n;
	size_t	max_size_t;

	max_size_t = (size_t)-1;
	if (nmemb != 0 && size > max_size_t / nmemb)
		return (NULL);
	n = nmemb * size;
	p = (void *) malloc(n);
	if (p == NULL)
		return (NULL);
	ft_bzero(p, n);
	return (p);
}
