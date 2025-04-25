/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:51:21 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/25 10:11:28 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_list(t_mini *mini)
{
	mini->tokens = create_list(mini->args);
	if (mini->tokens == NULL)
	{
		mini->exit_code = 1;
		return (1);
	}
	assign_operator(mini->tokens);
	if (is_valid_token(mini->tokens) == FALSE)
	{
		mini->exit_code = 2;
		return (1);
	}
	is_dollar_alone(mini);
	if (is_tilde(mini) == 1)
	{
		mini->exit_code = 1;
		return (1);
	}
	return (0);
}

static int	check_operator(t_mini *mini)
{
	if (is_even_quotes(mini->args) == FALSE)
	{
		free_array(mini->args);
		mini->exit_code = 1;
		return (1);
	}
	if (is_valid_operator(mini->args) == FALSE)
	{
		free_array(mini->args);
		mini->exit_code = 2;
		return (1);
	}
	return (0);
}

t_command	*parsing(t_mini *mini)
{
	mini->args = arg_split(mini->input);
	if (mini->args == NULL)
	{
		error_arg_split(mini);
		return (NULL);
	}
	if (check_operator(mini) == 1)
		return (NULL);
	if (handle_list(mini) == 1)
		return (NULL);
	if (expander(mini) == 1)
	{
		write(STDERR_FILENO, "memory allocation failed in expander\n", 37);
		return (NULL);
	}
	assign_type_argument(mini->tokens);
	if (merge_args(&mini->tokens) == FALSE)
	{
		error_merge_args(mini);
		return (NULL);
	}
	mini->cmds = split_pipe(mini->tokens, NULL, NULL, 0);
	if (mini->cmds == NULL)
	{
		error_split_pipe(mini);
		return (NULL);
	}
	free_token(mini->tokens);
	return (mini->cmds);
}
