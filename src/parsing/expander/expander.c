/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:04:18 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/07 13:25:45 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	find_dollar(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '$')
// 			return (i);
// 		i++;
// 	}
// 	return (-1);
// }

// static char	*expand_special_vars(char *arg, t_mini *mini)
// {
// 	int		index;
// 	char	*result;
// 	char	*full_string;
// 	char	*partial_string;
// 	int		len;
// 	int		i;
// 	char	*new_arg;

// 	i = 0;
// 	index = find_dollar(arg);
// 	len = ft_strlen(arg);
// 	if (ft_strncmp(arg, "$?", 2) == 0 && len == 2)
// 	{
// 		result = ft_itoa(mini->exit_code);
// 		free(arg);
// 		return (result);
// 	}
// 	else if (ft_strncmp(arg, "$?", 2) == 0 && len > 2)
// 	{
// 		while (arg[i + 1])
// 		{
// 			if (arg[i] == '$' && arg[i + 1] == '?')
// 			{
// 				result == *ft_itoa(mini->exit_code);
// 			}
// 			i++;
// 		}
// 		result = ft_itoa(mini->exit_code);
// 		partial_string = ft_substr(arg, 2, ft_strlen(arg) - 2);
// 		full_string = ft_strjoin(result, partial_string);
// 		free(arg);
// 		free(partial_string);
// 		return (full_string);
// 	}
// 	return (arg);
// }

static char	*expand_special_vars(char *arg, t_mini *mini)
{
	int		i;
	char	*exit_str;
	char	*before_str;
	char	*new_arg;
	int		len;
	char	*after_str;
	char	*full_str;
	char	*temp;

	i = 0;
	len = ft_strlen(arg);
	exit_str = ft_itoa(mini->exit_code);
	if (ft_strncmp(arg, "$?", 2) == 0 && len == 2)
	{
		free(arg);
		return (exit_str);
	}
	else if (ft_strncmp(arg, "$?", 2) == 0 && len > 2)
	{
		full_str = ft_strdup(arg);
		while (arg[i + 1])
		{
			if (full_str[i] == '$' && full_str[i + 1] == '?')
			{
				before_str = ft_substr(full_str, 0, i);
				after_str = ft_substr(full_str, i + 2, ft_strlen(full_str) - i
						- 2);
				new_arg = ft_strjoin(before_str, exit_str);
				temp = full_str;
				full_str = ft_strjoin(new_arg, after_str);
				free(temp);
				free(before_str);
				free(after_str);
				free(new_arg);
				i += ft_strlen(exit_str);
			}
			else
				i++;
		}
		free(exit_str);
		free(arg);
		return (full_str);
	}
	free(exit_str);
	return (arg);
}

void	expander(t_mini *mini)
{
	int			i;
	t_command	*current;

	current = mini->cmds;
	while (current)
	{
		i = 0;
		while (current->argv && current->argv[i])
		{
			current->argv[i] = expand_special_vars(current->argv[i], mini);
			i++;
		}
		current = current->next;
	}
}
