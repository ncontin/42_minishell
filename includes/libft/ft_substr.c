/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 08:35:16 by aroullea          #+#    #+#             */
/*   Updated: 2024/10/18 10:39:11 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static char	*ft_alloc(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	i;
	size_t	size_malloc;

	i = 0;
	p = NULL;
	if (ft_strlen(s + start) < len)
		size_malloc = ft_strlen(s + start) + 1;
	else
		size_malloc = len + 1;
	p = malloc(size_malloc);
	if (p == NULL)
		return (NULL);
	while (i < len)
	{
		p[i] = s[start];
		i++;
		start++;
	}
	p[i] = '\0';
	return (p);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;

	p = NULL;
	if (s == NULL)
		return (0);
	if (start >= ft_strlen(s))
	{
		p = malloc(sizeof(char));
		if (p == NULL)
			return (NULL);
		p[0] = '\0';
		return (p);
	}
	else
	{
		if (len >= ft_strlen(s))
			p = ft_alloc(s, start, (ft_strlen(s) - start));
		else
			p = ft_alloc(s, start, len);
	}
	return (p);
}
