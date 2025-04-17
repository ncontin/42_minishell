/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:11:43 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/17 16:53:04 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_word_len(char *arg, int len)
{
	len = 0;
	while (arg[len] && (ft_isspace(arg[len]) == 0)
		&& (ft_isspecial(arg[len]) == 0))
		len++;
	return (len);
}

static char	*process_string(char *full_str, t_env_node *current,
		unsigned long len, int i)
{
	char	*before_str;
	char	*after_str;
	char	*temp;

	before_str = ft_substr(full_str, 0, i);
	after_str = ft_substr(full_str, i + len + 1, ft_strlen(full_str) - i - len
			- 1);
	if (!current->value)
		temp = ft_strjoin(before_str, "");
	else
		temp = ft_strjoin(before_str, current->value);
	free(before_str);
	free(full_str);
	full_str = ft_strjoin(temp, after_str);
	free(after_str);
	free(temp);
	return (full_str);
}

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

static char	*replace_env_vars(char *full_str, t_mini *mini, int i)
{
	t_env_node		*current;
	unsigned long	len;
	int				find;

	find = 0;
	current = *mini->lst_env->envp_cp;
	while (current)
	{
		len = find_word_len(&full_str[i + 1], i);
		if (ft_strncmp(&full_str[i + 1], current->key, len) == 0
			&& ft_strlen(current->key) == len)
		{
			// printf("mini->tokens->quotes: %s\n", mini->tokens->quotes);
			full_str = process_string(full_str, current, len, i);
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

char	*expand_shell_vars(char *arg, t_mini *mini)
{
	int		i;
	char	*full_str;

	if (arg == NULL)
		return (NULL);
	i = 0;
	while (ft_isprint(arg[i]) && arg[i] != '$')
		i++;
	if (arg[i] == '\0')
		return (arg);
	full_str = ft_strdup(arg);
	while (full_str[i])
	{
		if (full_str[i] == '$' && (full_str[i + 1] && (ft_isspecial(full_str[i
						+ 1]) == 0)))
		{
			full_str = replace_env_vars(full_str, mini, i);
			mini->expanded = 1;
			if (full_str && full_str[0] == '\0')
			{
				free(arg);
				free(full_str);
				return (NULL);
			}
		}
		i++;
	}
	free(arg);
	return (full_str);
}
