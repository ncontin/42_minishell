/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_argument.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:12:05 by aroullea          #+#    #+#             */
/*   Updated: 2025/03/28 11:57:34 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	replace_argument(t_token *tokens, t_env *env)
{
	t_env_node	**env_table;
	int			i;

	i = 0;
	env_table = env->envp_cp;
	while (env_table[i])
	{
		if (ft_strncmp(tokens->argument + 1, env_table[i]->key, ft_strlen(tokens->argument+1)) == 0)
		{
			free(tokens->argument);
			tokens->argument = env_table[i]->value;
			break ;
		}
		env_table[i] = env_table[i]->next;
	}
}

void	get_env_argument(t_mini *mini)
{
	t_token *tokens;

	tokens = mini->tokens;
	while (tokens != NULL)
	{
		if (tokens->arg_type == ENV_VAR)
			replace_argument(tokens, mini->lst_env);
		tokens = tokens->next;
	}
}
