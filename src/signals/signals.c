/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:08:22 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/01 15:55:41 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		signal_received = 0;

void	sig_handler(int signal)
{
	if (signal == SIGINT)
		printf("\nminishell> ");
	if (signal == SIGQUIT)
		return ;
}
