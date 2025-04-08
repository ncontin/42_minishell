/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:31:12 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/07 18:04:47 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_msg(char *message, int error)
{
	write(STDERR_FILENO, message, ft_strlen(message) + 1);
	write(STDERR_FILENO, "\n", 1);
	exit(error);
}
