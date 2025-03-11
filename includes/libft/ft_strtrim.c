/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:18:02 by aroullea          #+#    #+#             */
/*   Updated: 2024/10/21 09:54:05 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static size_t	ft_size_end(char const *s1, char const *set, size_t i, size_t l)
{
	size_t	j;
	int		find;

	j = ft_strlen(s1);
	find = 1;
	if (*set == '\0')
		find = 0;
	while (find == 1)
	{
		while (set[i])
		{
			if (set[i] == s1[j - 1])
			{
				find = 1;
				l++;
				break ;
			}
			else
				find = 0;
			i++;
		}
		i = 0;
		j--;
	}
	return (l);
}

static size_t	ft_size_sta(char const *s1, char const *set, size_t i, size_t j)
{
	size_t	l;
	int		find;

	l = 0;
	find = 1;
	if (*set == '\0')
		find = 0;
	while (find == 1)
	{
		while (set[i])
		{
			if (set[i] == s1[j])
			{
				find = 1;
				l++;
				break ;
			}
			else
				find = 0;
			i++;
		}
		i = 0;
		j++;
	}
	return (l);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		i;
	int		size;
	size_t	start;
	size_t	end;

	if (!s1 || !set)
		return (0);
	i = 0;
	start = ft_size_sta(s1, set, 0, 0);
	end = ft_size_end(s1, set, 0, 0);
	size = ft_strlen(s1) - (start + end);
	if (size < 0)
		size = 0;
	str = malloc ((sizeof(char) * size) + 1);
	if (str == NULL)
		return (NULL);
	while (i < size)
	{
		str[i] = s1[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}
