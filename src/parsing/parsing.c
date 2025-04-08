/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:51:21 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/07 18:25:52 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*parsing(t_mini *mini)
{
	mini->args = arg_split(mini->input);
	if (mini->args == NULL)
		return (NULL);
	if (is_even_quotes(mini->args) == FALSE)
		return (NULL);
	mini->tokens = create_list(mini->args);
	free_array(mini->args);
	if (mini->tokens == NULL)
		return (NULL);
	assign_operator(mini->tokens);
	if (is_valid_token(mini->tokens) == FALSE)
	{
		free_token(mini->tokens);
		return (NULL);
	}
	assign_type_argument(mini->tokens);
	if (merge_args(&mini->tokens) == FALSE)
		return (NULL);
	mini->cmds = split_pipes(mini->tokens, NULL, NULL);
	// get_env_argument(mini);
	expander(mini);
	free_token(mini->tokens);
	return (mini->cmds);
}
