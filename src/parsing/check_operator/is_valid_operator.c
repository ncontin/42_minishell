/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_operator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:52:29 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/30 19:18:26 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_valid_operator(char **args)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(args[i]);
	while (args[i] != NULL && len >= 2)
	{
		if (ft_strncmp(args[i], "||", len) == 0)
		{
			write(STDERR_FILENO, "syntax error near unexpected token `", 36);
			write(STDERR_FILENO, args[i], len);
			write(STDERR_FILENO, "'\n", 2);
			return (FALSE);
		}
		if (ft_strncmp(args[i], "&&", len) == 0)
		{
			write(STDERR_FILENO, "syntax error near unexpected token `", 36);
			write(STDERR_FILENO, args[i], len);
			write(STDERR_FILENO, "'\n", 2);
			return (FALSE);
		}
		i++;
		len = ft_strlen(args[i]);
	}
	return (TRUE);
}
