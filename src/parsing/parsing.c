/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:51:21 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/17 10:28:16 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*parsing(t_mini *mini)
{
	mini->args = arg_split(mini->input);
	if (mini->args == NULL)
	{
		write(STDERR_FILENO, "arg_split :", 11);
		write(STDERR_FILENO, "memory allocation failed\n", 25);
		free_exit(mini);
		exit(EXIT_FAILURE);
	}
	if (is_even_quotes(mini->args) == FALSE)
		return (NULL);
	mini->tokens = create_list(mini->args);
	free_array(mini->args);
	if (mini->tokens == NULL)
	{
		free_exit(mini);
		exit(EXIT_FAILURE);
	}
	assign_operator(mini->tokens);
	if (is_valid_token(mini->tokens) == FALSE)
	{
		mini->exit_code = 2;
		free_token_argument(mini->tokens);
		free_token(mini->tokens);
		return (NULL);
	}
	expander(mini);
	assign_type_argument(mini->tokens);
	if (merge_args(&mini->tokens) == FALSE)
		return (NULL);
	mini->cmds = split_pipe(mini->tokens, NULL, NULL, 0);
	free_token(mini->tokens);
	return (mini->cmds);
}
