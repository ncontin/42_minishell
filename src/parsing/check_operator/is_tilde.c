/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_tilde.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:04:55 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/22 21:02:49 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	error_handle_tilde(t_mini *mini)
{
	write(STDERR_FILENO, "Memory allocation failed for is_tilde\n", 38);
	free_token_argument(mini->tokens);
	free_token(mini->tokens);
	free_exit(mini);
	exit (EXIT_FAILURE);
}

static void	handle_tilde(char **source, t_mini *mini)
{
	t_env_node	*current;
	char		*str;
	char		*arg;

	arg = *source;
	current = *mini->lst_env->envp_cp;
	while (current != NULL)
	{
		if (strncmp(current->key, "HOME", ft_strlen(current->key) + 1) == 0)
		{
			if (current->value != NULL)
			{
				str = ft_strdup(current->value);
				if (str == NULL)
					error_handle_tilde(mini);
				*source = ft_strjoin(str, arg + 1);
				if (*source == NULL)
				{
					free(str);
					error_handle_tilde(mini);
				}
				free(str);
				free(arg);
			}
			break ;
		}
		current = current->next;
	}
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
					&& current->next->argument != NULL && current->next->argument[0] == '/'))
				handle_tilde(&current->argument, mini);
			}
		}
		current = current->next;
	}
	return (0);
}
