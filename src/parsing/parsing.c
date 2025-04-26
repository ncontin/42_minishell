/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:51:21 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/26 17:22:07 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_tokens(t_mini *mini)
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

static int	validate_operators(t_mini *mini)
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

static int	prepare_tokens(t_mini *mini)
{
	mini->args = arg_split(mini->input);
	if (!mini->args)
	{
		error_arg_split(mini);
		return (1);
	}
	if (validate_operators(mini) == 1)
		return (1);
	if (process_tokens(mini) == 1)
		return (1);
	if (expander(mini, NULL, NULL) == 1)
	{
		write(STDERR_FILENO, "memory allocation failed in expander\n", 37);
		return (1);
	}
	assign_type_argument(mini->tokens);
	return (0);
}

static t_command	*build_commands(t_mini *mini)
{
	if (!merge_args(&mini->tokens))
	{
		error_merge_args(mini);
		return (NULL);
	}
	mini->cmds = split_pipe(mini->tokens, NULL, NULL, 0);
	if (!mini->cmds)
	{
		error_split_pipe(mini);
		return (NULL);
	}
	free_token(mini->tokens);
	return (mini->cmds);
}

t_command	*parsing(t_mini *mini)
{
	if (prepare_tokens(mini) == 1)
		return (NULL);
	mini->cmds = build_commands(mini);
	return (mini->cmds);
}
