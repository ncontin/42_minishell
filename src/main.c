/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:10:37 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/29 11:13:58 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal_received = 0;

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;

	if (argc >= 2)
	{
		write(2, "Too many arguments \n", 20);
		return (1);
	}
	(void)argv;
	init_mini(&mini);
	get_path(envp, mini.lst_env);
	init_envp(&mini);
	line_read(&mini);
	return (0);
}
