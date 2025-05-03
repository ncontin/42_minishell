/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:11:53 by ncontin           #+#    #+#             */
/*   Updated: 2025/05/03 09:42:41 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	extract_part(char *full_str, int i, char **before, char **after)
{
	int	len;

	len = ft_strlen(full_str);
	*before = handle_substr(full_str, 0, i);
	if (*before == NULL)
		return (1);
	*after = handle_substr(full_str, i + 2, len - i - 2);
	if (*after == NULL)
	{
		free(*before);
		*before = NULL;
		return (1);
	}
	return (0);
}

static char	*process_string(char *full_str, int i, char *exit_str)
{
	char	*before_str;
	char	*after_str;
	char	*tmp;
	char	*result;

	tmp = NULL;
	before_str = NULL;
	after_str = NULL;
	result = NULL;
	if (extract_part(full_str, i, &before_str, &after_str) == 1)
	{
		free(full_str);
		return (NULL);
	}
	tmp = handle_strjoin(before_str, exit_str);
	if (!tmp)
	{
		free_three(full_str, before_str, after_str);
		return (NULL);
	}
	result = handle_strjoin(tmp, after_str);
	free_three(full_str, before_str, after_str);
	free(tmp);
	//if (!result)
		//return (NULL);
	return (result);
}

static char	*replace_exit_var(char *arg, char *exit_str)
{
	int		i;
	char	*full_str;

	full_str = ft_strdup(arg);
	if (full_str == NULL)
		return (NULL);
	i = 0;
	while (full_str[i])
	{
		if (full_str[i] == '$' && full_str[i + 1] == '?')
		{
			full_str = process_string(full_str, i, exit_str);
			if (full_str == NULL)
				break ;
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

	len = ft_strlen(arg);
	exit_str = ft_itoa(mini->exit_code);
	if (exit_str == NULL)
	{
		free(arg);
		return (NULL);
	}
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
