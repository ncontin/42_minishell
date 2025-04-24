/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:48:48 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/24 19:20:09 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int	check_digit(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	if (len == 0)
		return (1);
	if ((str[0] == '-' || str[0] == '+'))
	{
		if (len == 1)
			return (1);
		i++;
	}
	if (!ft_isdigit(str[i]))
		return (1);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

char	*del_spaces(char *str)
{
	char	*res;
	char	*temp;

	if (!str)
		return (NULL);
	temp = ft_strdup(str);
	res = ft_strtrim(temp, " ");
	free(temp);
	return (res);
}
