/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:03:52 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/15 12:59:22 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_overflow(const char *nptr, int *overflow)
{
	if (!nptr)
		return (0);
	*overflow = 0;
	ft_atoll(nptr, overflow);
	return (*overflow == 1);
}

static int	check_digit(char *str)
{
	int	i;

	if (!str)
		return (0);
	if (!*str)
		return (1);
	i = 0;
	if ((str[i] == '-' && ft_isdigit(str[i + 1])) || (str[i] == '+'
			&& ft_isdigit(str[i + 1])))
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

static char	*del_spaces(char *str)
{
	char	*res;
	char	*temp;

	if (!str)
		return (NULL);
	temp = ft_strdup(str);
	res = ft_strtrim(temp, " ");
	free(temp);
	return (res);
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

void	ft_exit(t_mini *mini, char **cmd_args)
{
	int		overflow;
	char	*arg;

	overflow = 0;
	arg = NULL;
	if (isatty(STDIN_FILENO))
		ft_putstr_fd("exit\n", STDERR_FILENO);
	if (cmd_args && cmd_args[1])
	{
		arg = del_spaces(cmd_args[1]);
		if (!arg)
		{
			perror("minishell: exit");
			mini->exit_code = 1;
		}
		else if (check_digit(arg) == 1 || check_overflow(arg, &overflow) == 1)
		{
			print_error(mini, cmd_args[1]);
			free(arg);
			free_exit(mini);
			rl_clear_history();
			exit(mini->exit_code);
		}
		else if (cmd_args[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n",
				STDERR_FILENO);
			mini->exit_code = 1;
			free(arg);
			return ;
		}
		else
			mini->exit_code = ft_atoll(arg, &overflow);
	}
	mini->exit_code = mini->exit_code % 256;
	if (arg)
		free(arg);
	free_exit(mini);
	rl_clear_history();
	exit(mini->exit_code);
}
