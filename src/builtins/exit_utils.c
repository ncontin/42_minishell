/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:48:48 by ncontin           #+#    #+#             */
/*   Updated: 2025/05/01 12:57:22 by aroullea         ###   ########.fr       */
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

static char	check_is_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

static char	*handle_temp(char *str)
{
	char	*temp;

	temp = ft_strdup(str);
	if (temp == NULL)
	{
		write(STDERR_FILENO, "memory allocation failed in exit\n", 33);
		return (NULL);
	}
	return (temp);
}

char	*del_spaces(char *str)
{
	char	*res;
	char	*temp;

	if (!str)
		return (NULL);
	if (check_is_spaces(str) == 0)
	{
		temp = handle_temp("");
		return (temp);
	}
	else
	{
		temp = handle_temp(str);
		if (temp == NULL)
			return (NULL);
	}
	res = ft_strtrim(temp, " ");
	free(temp);
	if (res == NULL)
	{
		write(STDERR_FILENO, "memory allocation failed in exit\n", 33);
		return (NULL);
	}
	return (res);
}

int	is_double_dash(char **cmd_args)
{
	if (cmd_args && ft_strncmp(cmd_args[1], "--\0", 3) == 0)
		return (1);
	return (0);
}
