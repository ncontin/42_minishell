/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:51:21 by aroullea          #+#    #+#             */
/*   Updated: 2025/03/31 17:56:41 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*parsing(t_mini *mini)
{
	t_command	*cmds;
	
	mini->args = arg_split(mini->input);
	if (mini->args == NULL)
		return (NULL);
	if (is_even_quotes(mini->args) == FALSE)
		return (NULL);
	mini->tokens = create_list(mini->args);
	if (mini->tokens == NULL)
		return (NULL);
	assign_operator(mini->tokens);
	if (is_valid_token(mini->tokens) == FALSE)
	{
		free_token(mini->tokens);
		return (NULL);
	}
	assign_type_argument(mini->tokens);
	get_env_argument(mini);
	mini->tokens = merge_args(mini->tokens);
	if (mini->tokens == NULL)
		return (NULL);
	cmds = split_pipes(mini->tokens, NULL, NULL);
	//if (is_builtin(mini->args[0]))
		//execute_builtin(mini);
	//free_token(mini->tokens);
	return (cmd);
}
