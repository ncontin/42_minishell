/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_argument.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 15:39:54 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/04 17:06:52 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	replace_argument(t_token *tokens, t_mini *mini)
{
	t_env_node	*current;
	char		*arg;
	int			i;

	i = 0;
	current = *mini->lst_env->envp_cp;
	arg = tokens->argument;
	while (i < 2)
	{
		while (current)
		{
			if (ft_strncmp(arg + 1, current->key, ft_strlen(arg + 1)) == 0)
			{
				free(tokens->argument);
				tokens->argument = ft_strdup(current->value);
				return ;
			}
			current = current->next;
		}
		i++;
	}
	free(tokens->argument);
	tokens->argument = NULL;
}

void	get_env_argument(t_mini *mini)
{
	t_token	*tokens;

	tokens = mini->tokens;
	while (tokens != NULL)
	{
		if (tokens->arg_type == ENV_VAR && tokens->quotes != SINGLE)
			replace_argument(tokens, mini);
		tokens = tokens->next;
	}
}
