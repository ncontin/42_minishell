/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:51:21 by aroullea          #+#    #+#             */
/*   Updated: 2025/03/28 11:30:33 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(t_mini *mini)
{
	t_bool	even_quotes;

	mini->args = arg_split(mini->input);
	if (mini->args == NULL)
		return ;
	even_quotes = is_even_quotes(mini->args);
	if (even_quotes == FALSE)
		return ;
	mini->tokens = create_list(mini->args);
	if (mini->tokens == NULL)
		return ;
	assign_operator(mini->tokens);
	if (is_valid_token(mini->tokens) == FALSE)
	{
		free_token(mini->tokens);
		return ;
	}
	assign_type_argument(mini->tokens);
	get_env_argument(mini);
	/*if (mini->lst_env->envp_cp[0] != NULL)
	{
		int	i = 0;
		while ((mini->lst_env->envp_cp[i]) && (i < 3))
		{
			printf("\n\n%s\n", mini->lst_env->envp_cp[i]->key);
			printf("%s\n\n", mini->lst_env->envp_cp[i]->value);
			i++;
		}
	}*/
	if (is_builtin(mini->args[0]))
		execute_builtin(mini);
	free_token(mini->tokens);
}
