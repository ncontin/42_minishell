/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:11:43 by ncontin           #+#    #+#             */
/*   Updated: 2025/05/03 09:25:21 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*replace_env_var(char *full_str, t_mini *mini, int i, int *err_code)
{
	t_env			*current;
	unsigned long	len;

	current = mini->envp_cp;
	while (current)
	{
		len = find_word_len(&full_str[i + 1], i);
		if (ft_strncmp(&full_str[i + 1], current->key, len) == 0
			&& ft_strlen(current->key) == len)
		{
			full_str = get_env_var(full_str, current, i, err_code);
			return (full_str);
		}
		current = current->next;
	}
	full_str = no_args(full_str, i, err_code);
	return (full_str);
}

static char	*process_var(char *full_str, t_mini *mini, int i, int *err_code)
{
	mini->expanded = 0;
	while (full_str && full_str[i])
	{
		if (full_str[i] == '$')
		{
			if (full_str[i + 1] && !ft_isspecial(full_str[i + 1]))
			{
				full_str = replace_env_var(full_str, mini, i, err_code);
				mini->expanded = 1;
				i--;
				if (full_str && full_str[0] == '\0')
				{
					free(full_str);
					return (NULL);
				}
			}
		}
		i++;
	}
	return (full_str);
}

char	*expand_shell_vars(char *arg, t_mini *mini, int *err_code)
{
	int		i;
	char	*full_str;

	if (!arg)
		return (NULL);
	i = 0;
	while (arg[i] && ft_isprint(arg[i]) && arg[i] != '$')
		i++;
	if (arg[i] == '\0')
		return (arg);
	full_str = ft_strdup(arg);
	if (!full_str)
	{
		*err_code = 1;
		return (NULL);
	}
	full_str = process_var(full_str, mini, i, err_code);
	if (!full_str)
	{
		free(arg);
		return (NULL);
	}
	free(arg);
	return (full_str);
}
