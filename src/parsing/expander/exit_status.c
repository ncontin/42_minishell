/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:11:53 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/18 12:30:00 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*process_string(char *full_str, int i, char *exit_str)
{
	char	*before_str;
	char	*after_str;
	char	*new_arg;

	before_str = ft_substr(full_str, 0, i);
	after_str = ft_substr(full_str, i + 2, ft_strlen(full_str) - i - 2);
	new_arg = ft_strjoin(before_str, exit_str);
	free(before_str);
	free(full_str);
	full_str = ft_strjoin(new_arg, after_str);
	free(after_str);
	free(new_arg);
	return (full_str);
}

char	*replace_exit_var(char *arg, char *exit_str)
{
	int		i;
	char	*full_str;

	full_str = ft_strdup(arg);
	i = 0;
	while (full_str[i])
	{
		if (full_str[i] == '$' && full_str[i + 1] == '?')
		{
			full_str = process_string(full_str, i, exit_str);
			i += ft_strlen(exit_str) - 1;
		}
		i++;
	}
	free(exit_str);
	free(arg);
	return (full_str);
}

char	*expand_exit_status(char *arg, t_mini *mini)
{
	char	*exit_str;
	int		len;
	char	*full_str;

	if (arg == NULL)
		return (NULL);
	len = ft_strlen(arg);
	exit_str = ft_itoa(mini->exit_code);
	if (ft_strncmp(arg, "$?", 2) == 0 && len == 2)
	{
		free(arg);
		return (exit_str);
	}
	else
	{
		full_str = replace_exit_var(arg, exit_str);
		return (full_str);
	}
}
