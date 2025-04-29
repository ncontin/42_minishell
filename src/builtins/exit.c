/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:03:52 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/29 15:17:39 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_overflow(const char *nptr, int *overflow)
{
	if (!nptr)
		return (0);
	*overflow = 0;
	ft_atoll(nptr, overflow);
	return (*overflow == 1); //nessuna assegnazione di variabili in un return
}

static void	print_error(t_mini *mini, char *arg)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	if (arg)
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd("numeric argument required\n", STDERR_FILENO);
	mini->exit_code = 2;
}

static void	perform_exit(t_mini *mini, int exit_code)
{
	mini->exit_code = exit_code % 256;
	free_exit(mini);
	rl_clear_history();
	exit(mini->exit_code);
}

static int	validate_exit_arg(t_mini *mini, char *arg_str, char **arg)
{
	int	overflow;

	overflow = 0;
	*arg = del_spaces(arg_str);
	if (*arg == NULL)
	{
		perror("minishell: exit");
		mini->exit_code = 1;
		return (0);
	}
	if (check_digit(*arg) == 1 || check_overflow(*arg, &overflow) == 1)
	{
		print_error(mini, arg_str);
		free(*arg);
		perform_exit(mini, mini->exit_code);
	}
	return (1);
}

void	ft_exit(t_mini *mini, char **cmd_args)
{
	char	*arg;
	int		overflow;

	arg = NULL;
	overflow = 0;
	if (isatty(STDIN_FILENO))
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (cmd_args && cmd_args[1])
	{
		if (is_double_dash(cmd_args))
			perform_exit(mini, mini->exit_code);
		if (!validate_exit_arg(mini, cmd_args[1], &arg))
			return ;
		if (cmd_args[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n",
				STDERR_FILENO);
			mini->exit_code = 1;
			free(arg);
			return ;
		}
		mini->exit_code = ft_atoll(arg, &overflow);
		free(arg);
	}
	perform_exit(mini, mini->exit_code);
}
