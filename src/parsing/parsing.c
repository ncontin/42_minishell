/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:51:21 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/02 10:12:22 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(t_mini *mini)
{
	mini->args = arg_split(mini->input);
	if (mini->args == NULL)
		return ;
	if (is_even_quotes(mini->args) == FALSE)
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
	mini->tokens = merge_args(mini->tokens);
	if (mini->tokens == NULL)
		return ;
	mini->cmds = split_pipes(mini->tokens, NULL, NULL);
	//if (is_builtin(mini->args[0]))
		//execute_builtin(mini);
	//free_token(mini->tokens);
}
