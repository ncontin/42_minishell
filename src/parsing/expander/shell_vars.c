/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:11:43 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/26 10:51:26 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*process_no_args(char *full_str, unsigned long len, int i)
{
	char	*before_str;
	char	*after_str;
	char	*temp;

	before_str = ft_substr(full_str, 0, i);
	after_str = ft_substr(full_str, i + len + 1, ft_strlen(full_str) - i - len
			- 1);
	temp = ft_strjoin(before_str, after_str);
	free(before_str);
	free(after_str);
	free(full_str);
	return (temp);
}

static char	*replace_env_var(char *full_str, t_mini *mini, int i, int *err_code)
{
	t_env_node		*current;
	unsigned long	len;
	int				find;

	(void)err_code;
	find = 0;
	current = *mini->lst_env->envp_cp;
	while (current)
	{
		len = find_word_len(&full_str[i + 1], i);
		if (ft_strncmp(&full_str[i + 1], current->key, len) == 0
			&& ft_strlen(current->key) == len)
		{
			full_str = get_env_var(full_str, current, i, err_code);
			i += ft_strlen(current->value) - 1;
			find = 1;
			break ;
		}
		current = current->next;
	}
	if (find == 0)
		full_str = process_no_args(full_str, len, i);
	return (full_str);
}

static char	*process_variables(char *full_str, t_mini *mini, int i,
		int *err_code)
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
	full_str = process_variables(full_str, mini, i, err_code);
	if (!full_str)
	{
		free(arg);
		return (NULL);
	}
	free(arg);
	return (full_str);
}
