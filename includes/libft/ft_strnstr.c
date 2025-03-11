/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 07:44:13 by aroullea          #+#    #+#             */
/*   Updated: 2024/10/11 06:55:00 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	chartest(char *cbig, char *clittle, unsigned long int i, size_t len)
{
	int	j;
	int	test;

	j = 0;
	test = 1;
	while (i < len && clittle[j] != '\0' && test != 0)
	{
		test = cbig[i] == clittle[j];
		i++;
		j++;
	}
	if (i == len && clittle[j] != '\0')
		return (0);
	return (test);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	int		search;
	char	*cbig;
	char	*clittle;

	cbig = (char *)big;
	clittle = (char *)little;
	search = 0;
	i = 0;
	if (clittle[i] == '\0')
		return (cbig);
	else
	{
		while (i < len && cbig[i] != '\0' && !search)
		{
			if (cbig[i] == clittle[0])
			{
				search = chartest(cbig, clittle, i, len);
				if (search)
					return (cbig + i);
			}
			i++;
		}
	}
	return (NULL);
}
