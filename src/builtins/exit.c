/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:03:52 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/01 10:52:04 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_overflow(const char *nptr, int *overflow)
{
	int	len;

	if (!nptr)
		return (0);
	len = ft_strlen(nptr);
	if ((nptr[0] == '-' || nptr[0] == '+') && len > 20)
		return (1);
	else if ((nptr[0] != '-' && nptr[0] != '+') && len > 19)
		return (1);
	if (nptr)
		ft_atoll(nptr, overflow);
	if (*overflow == 1)
		return (1);
	return (0);
}

static int	check_digit(char *str)
{
	int	i;

	if (!str)
		return (0);
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

static char	*parse_arg(char *str)
{
	char	*res;

	if (!str)
		return (NULL);
	res = ft_strtrim(ft_strtrim(str, "\""), " ");
	return (res);
}

void	ft_exit(t_mini *mini)
{
	int		overflow;
	char	*arg;

	overflow = 0;
	arg = parse_arg(mini->args[1]);
	if (check_overflow(arg, &overflow) == 1 || check_digit(arg) == 1)
	{
		ft_putstr_fd("exit\nminishell: exit: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		mini->exit_code = 2;
	}
	else if (mini->args[0] && arg && mini->args[2])
	{
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
		mini->exit_code = 1;
		return ;
	}
	else if (mini->args[0] && arg)
		mini->exit_code = ft_atoll(arg, &overflow);
	mini->exit_code = mini->exit_code % 256;
	free_all(mini);
	rl_clear_history();
	exit(mini->exit_code);
}
