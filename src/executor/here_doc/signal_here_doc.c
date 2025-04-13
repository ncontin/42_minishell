/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 12:09:29 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/13 19:36:46 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void here_doc_handler(int signal)
{
    if (signal == SIGINT)
    {
        signal_received = 1;
		printf("\n");
    }
}

void	here_doc_signal(void)
{
	struct sigaction    sa;

	sa.sa_handler = here_doc_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}
