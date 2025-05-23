/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:08:22 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/17 09:43:54 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		g_signal_received = 1;
		rl_redisplay();
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		if (!rl_line_buffer && !*rl_line_buffer)
			rl_redisplay();
	}
}

void	handle_signals(void)
{
	struct sigaction	signals;

	signals.sa_handler = sig_handler;
	sigemptyset(&signals.sa_mask);
	signals.sa_flags = SA_RESTART;
	sigaction(SIGINT, &signals, NULL);
	signals.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &signals, NULL);
}
