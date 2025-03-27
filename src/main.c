/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:10:37 by aroullea          #+#    #+#             */
/*   Updated: 2025/03/27 09:00:23 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	lst_env;
	t_mini	mini;

	(void)argc;
	(void)argv;
	mini.lst_env = &lst_env;
	get_path(envp, &lst_env);
	init_envp(&lst_env);
	line_read(&mini);
}
