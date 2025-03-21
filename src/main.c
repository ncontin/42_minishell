/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:10:37 by aroullea          #+#    #+#             */
/*   Updated: 2025/03/21 12:43:41 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	lst_env;

	(void)argc;
	(void)argv;
	get_path(envp, &lst_env);
	init_envp(&lst_env);
	line_read(&lst_env);
	free_struct(&lst_env);
	free_stack(lst_env.envp_cp);
}
