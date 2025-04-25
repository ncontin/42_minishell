/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:55:46 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/25 13:36:45 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error_cd(char *msg, char *arg)
{
	write(STDERR_FILENO, "cd: ", 4);
	write(STDERR_FILENO, arg, ft_strlen(arg));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\n", 1);
}

void	print_error_chdir(char *path, char *pwd, t_mini *mini)
{
	free(pwd);
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	perror(NULL);
	mini->exit_code = 1;
}
