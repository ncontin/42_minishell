/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:03:52 by ncontin           #+#    #+#             */
/*   Updated: 2025/03/27 15:39:57 by ncontin          ###   ########.fr       */
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

long int	ft_atoll(const char *nptr)
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

void	ft_exit(t_mini *mini)
{
	long long int	exit_code;

	exit_code = 0;
	if (mini->args[0] && mini->args[1] && check_overflow(mini->args[1]) != 1)
		exit_code = ft_atoll(mini->args[1]);
	else if (check_overflow(mini->args[1]) == 1)
	{
		printf("minishell: exit: %s: numeric argument required\n",
			mini->args[1]);
		exit_code = 2;
	}
	else
		exit_code = exit_code % 256;
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
	rl_clear_history();
	exit(exit_code);
}
