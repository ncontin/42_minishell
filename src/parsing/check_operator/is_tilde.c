/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_tilde.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:04:55 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/24 23:24:27 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	rep_tilde(char **source, char *arg, t_env_node *env)
{
	char	*str;
	
	str = ft_strdup(env->value);
	if (str == NULL)
	{
		write(STDERR_FILENO, "Memory allocation failed for is_tilde\n", 38);
		return (1);
	}
	*source = ft_strjoin(str, arg + 1);
	if (*source == NULL)
	{
		free(str);
		write(STDERR_FILENO, "Memory allocation failed for is_tilde\n", 38);
		return (1);
	}
	free(str);
	free(arg);
	return (0);
}

static int	handle_tilde(char **source, t_mini *mini)
{
	t_env_node	*current;
	char		*arg;

	arg = *source;
	current = *mini->lst_env->envp_cp;
	while (current != NULL)
	{
		if (strncmp(current->key, "HOME", ft_strlen(current->key) + 1) == 0)
		{
			if (current->value != NULL)
			{
				if (rep_tilde(source, arg, current) == 1)
					return (1);
				return (0);
			}
		}
		current = current->next;
	}
	return (0);
}

int	is_tilde(t_mini *mini)
{
	t_token	*current;

	current = mini->tokens;
	while (current != NULL)
	{
		if (current->argument != NULL && current->argument[0] == '~')
		{
			if (current->argument[1] == '\0' || current->argument[1] == '/')
			{
				if (current->linked == FALSE || (current->linked == TRUE
						&& current->next->argument != NULL
						&& current->next->argument[0] == '/'))
					if (handle_tilde(&current->argument, mini) == 1)
						return (1);
			}
		}
		current = current->next;
	}
	return (0);
}
