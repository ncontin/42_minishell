/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:03:52 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/04 17:52:31 by ncontin          ###   ########.fr       */
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

static char	*del_quotes_and_spaces(char *str)
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
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	mini->exit_code = 2;
}

void	ft_exit(t_mini *mini, char **cmd_args)
{
	int		overflow;
	char	*arg;

	overflow = 0;
	arg = NULL;
	if (cmd_args && cmd_args[0])
	{
		ft_putstr_fd("exit\n", 2);
		if (cmd_args && cmd_args[1] && cmd_args[1][0] != '\0')
			arg = del_quotes_and_spaces(cmd_args[1]);
		if (check_overflow(arg, &overflow) == 1 || check_digit(arg) == 1)
			print_error(mini, arg);
		else if (arg && cmd_args[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			mini->exit_code = 1;
			free(arg);
			return ;
		}
		else if (arg)
			mini->exit_code = ft_atoll(arg, &overflow);
	}
	mini->exit_code = mini->exit_code % 256;
	if (arg)
		free(arg);
	free_all(mini);
	rl_clear_history();
	exit(mini->exit_code);
}
