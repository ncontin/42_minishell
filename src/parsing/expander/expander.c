/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:04:18 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/08 17:06:59 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_exit_status(char *arg, t_mini *mini)
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
	else /* if (ft_strncmp(arg, "$?", 2) == 0 && len > 2) */
	{
		full_str = ft_strdup(arg);
		while (full_str[i])
		{
			if (full_str[i] == '$' && full_str[i + 1] == '?')
			{
				before_str = ft_substr(full_str, 0, i);
				after_str = ft_substr(full_str, i + 2, ft_strlen(full_str) - i
						- 2);
				new_arg = ft_strjoin(before_str, exit_str);
				temp = ft_strjoin(new_arg, after_str);
				free(full_str);
				full_str = temp;
				free(before_str);
				free(after_str);
				free(new_arg);
				i += ft_strlen(exit_str) - 1;
			}
			i++;
		}
		free(exit_str);
		free(arg);
		return (full_str);
	}
	free(exit_str);
	return (arg);
}

// static void	replace_argument(t_token *tokens, t_mini *mini)
// {
// 	t_env_node	*current;
// 	char		*arg;
// 	int			i;

// 	i = 0;
// 	arg = tokens->argument;
// 	while (i < 2)
// 	{
// 		current = *mini->lst_env->envp_cp;
// 		while (current)
// 		{
// 			if (ft_strncmp(arg + 1, current->key, ft_strlen(arg + 1)) == 0)
// 			{
// 				free(tokens->argument);
// 				tokens->argument = ft_strdup(current->value);
// 				return ;
// 			}
// 			current = current->next;
// 		}
// 		i++;
// 	}
// 	free(tokens->argument);
// 	tokens->argument = NULL;
// }

// void	get_env_argument(t_mini *mini)
// {
// 	t_token	*tokens;

// 	tokens = mini->tokens;
// 	while (tokens != NULL)
// 	{
// 		if (tokens->arg_type == ENV_VAR && tokens->quotes != SINGLE)
// 			replace_argument(tokens, mini);
// 		tokens = tokens->next;
// 	}
// }

int	find_len(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != ' ')
		i++;
	return (i);
}

static char	*expand_shell_vars(char *arg, t_mini *mini)
{
	int			i;
	t_env_node	*current;
	char		*before_str;
	char		*after_str;
	char		*full_str;
	int			len;

	len = 0;
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '$' && arg[i + 1])
		{
			current = *mini->lst_env->envp_cp;
			while (current)
			{
				if (ft_strncmp(&arg[i + 1], current->key, ft_strlen(&arg[i
							+ 1])) == 0)
				{
					before_str = ft_substr(arg, 0, i);
					after_str = ft_strdup(current->value);
					full_str = ft_strjoin(before_str, after_str);
					free(before_str);
					free(after_str);
					return (full_str);
				}
				current = current->next;
			}
		}
		i++;
	}
	return (arg);
}

static char	*expand_special_vars(char *arg, t_mini *mini)
{
	arg = expand_exit_status(arg, mini);
	arg = expand_shell_vars(arg, mini);
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
