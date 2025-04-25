/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:23:32 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/25 06:47:09 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_word_len(char *arg, int len)
{
	len = 0;
	while (arg[len] && (ft_isspace(arg[len]) == 0)
		&& (ft_isspecial(arg[len]) == 0))
		len++;
	return (len);
}

int	has_space(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

int	get_array_size(char **array)
{
	int	counter;

	counter = 0;
	while (array[counter])
		counter++;
	return (counter);
}

int	is_nl_char(t_token **tokens)
{
	if (ft_strncmp("\\n", (*tokens)->next->argument, 2) == 0
		|| ft_strncmp("\\r", (*tokens)->next->argument, 2) == 0
		|| ft_strncmp("\\t", (*tokens)->next->argument, 2) == 0)
		return (1);
	return (0);
}

int	is_dollar(t_token **tokens)
{
	if ((*tokens)->argument && (*tokens)->argument[0] == '$'
		&& (*tokens)->argument[1] == '\0')
		return (1);
	return (0);
}
