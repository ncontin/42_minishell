/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 06:25:28 by aroullea          #+#    #+#             */
/*   Updated: 2025/05/01 06:29:00 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expander_error(t_mini *mini, int *err_code)
{
	if (*err_code == 2)
	{
		write(STDERR_FILENO, "ambiguous redirect\n", 19);
		mini->exit_code = 1;
	}
	else
	{
		write(STDERR_FILENO, "memory allocation failed in expander\n", 37);
		mini->exit_code = 2;
	}
}
