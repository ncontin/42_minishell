/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:03:52 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/03 15:41:15 by ncontin          ###   ########.fr       */
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

// static char	*del_quotes_and_spaces(char *str)
// {
// 	char	*quoteless;
// 	char	*res;

// 	if (!str)
// 		return (NULL);
// 	quoteless = ft_strtrim(str, "\"");
// 	res = ft_strtrim(quoteless, " ");
// 	free(quoteless);
// 	return (res);
// }

static void	print_error(t_mini *mini, char *arg)
{
	ft_putstr_fd("exit\nminishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	mini->exit_code = 2;
}

void	ft_exit(t_mini *mini)
{
	int		overflow;
	char	*arg;

	overflow = 0;
	arg = NULL;
	// if (mini->cmds && mini->cmds->argv[0] != NULL
	// 	&& mini->cmds->argv[1] != NULL)
	// 	arg = del_quotes_and_spaces(mini->cmds->argv[1]);
	if (check_overflow(arg, &overflow) == 1 || check_digit(arg) == 1)
		print_error(mini, arg);
	else if (mini->cmds->argv != NULL && mini->cmds->argv[0] && arg
		&& mini->cmds->argv[2])
	{
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
		mini->exit_code = 1;
		free(arg);
		return ;
	}
	else if (mini->cmds->argv != NULL && mini->cmds->argv[0] && arg)
		mini->exit_code = ft_atoll(arg, &overflow);
	else if (mini->cmds->argv != NULL && mini->cmds->argv[0])
		ft_putstr_fd("exit\n", 2);
	mini->exit_code = mini->exit_code % 256;
	if (arg != NULL)
		free(arg);
	free_all(mini);
	rl_clear_history();
	exit(mini->exit_code);
}
