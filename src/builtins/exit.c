/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:03:52 by ncontin           #+#    #+#             */
/*   Updated: 2025/03/27 18:12:54 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_overflow(const char *nptr)
{
	if (!nptr)
		return (0);
	if (ft_strlen(nptr) > 20)
		return (1);
	else if (nptr[0] == '-' && ft_strlen(nptr) > 19)
		return (1);
	return (0);
}

long long int	ft_atoll(const char *nptr)
{
	int				i;
	int				sign;
	long long int	result;

	result = 0;
	sign = 1;
	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = (result * 10) + (nptr[i] - '0');
		i++;
	}
	return (result *= sign);
}

/* ➜  42_minishell git:(builtins) ✗ bash
ncontin@1D6:~/42/common_core/42_minishell$ exit -2
exit
➜  42_minishell git:(builtins) ✗ echo $?
254
➜  42_minishell git:(builtins) ✗ bash
ncontin@1D6:~/42/common_core/42_minishell$ exit -256
exit
➜  42_minishell git:(builtins) ✗ echo $?
0
➜  42_minishell git:(builtins) ✗ bash
ncontin@1D6:~/42/common_core/42_minishell$ exit -257
exit
➜  42_minishell git:(builtins) ✗ echo $?
255
➜  42_minishell git:(builtins) ✗ bash
ncontin@1D6:~/42/common_core/42_minishell$ exit 257
exit
➜  42_minishell git:(builtins) ✗ echo $?
1
 */

static int	check_digit(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

static void	free_all(t_mini *mini)
{
	if (mini->input)
		free(mini->input);
	if (mini->args)
		free_array(mini->args);
	if (mini->tokens)
		free_token(mini->tokens);
	if (mini->lst_env)
	{
		if (mini->lst_env->envp_cp)
			free_stack(mini->lst_env->envp_cp);
		if (mini->lst_env->envp_export)
			free_stack(mini->lst_env->envp_export);
		free_path(mini->lst_env);
	}
}

void	ft_exit(t_mini *mini)
{
	if (!mini->exit_code)
		mini->exit_code = 0;
	if (check_overflow(mini->args[1]) == 1 || check_digit(mini->args[1]) == 1)
	{
		ft_putstr_fd("exit\nminishell: exit: ", 2);
		ft_putstr_fd(mini->args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		mini->exit_code = 2;
	}
	else if (mini->args[0] && mini->args[1] && mini->args[2])
	{
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
		mini->exit_code = 1;
		return ;
	}
	if (mini->args[0] && mini->args[1] && check_overflow(mini->args[1]) != 1)
		mini->exit_code = ft_atoll(mini->args[1]);
	mini->exit_code = mini->exit_code % 256;
	free_all(mini);
	rl_clear_history();
	exit(mini->exit_code);
}
