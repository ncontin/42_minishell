/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:51:21 by aroullea          #+#    #+#             */
/*   Updated: 2025/05/04 10:46:45 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_tokens(t_mini *mini, char **args, t_token **tokens)
{
	*tokens = create_list(args);
	if (*tokens == NULL)
	{
		mini->exit_code = 2;
		return (1);
	}
	assign_operator(*tokens);
	if (is_valid_token(*tokens) == FALSE)
	{
		mini->exit_code = 2;
		return (1);
	}
	if (check_dollar(mini, *tokens) == 1)
		return (1);
	is_dollar_alone(*tokens);
	if (is_tilde(mini, *tokens) == 1)
	{
		mini->exit_code = 1;
		return (1);
	}
	return (0);
}

static int	validate_operators(t_mini *mini, char **args)
{
	if (is_even_quotes(args) == FALSE)
	{
		free_array(args);
		mini->exit_code = 1;
		return (1);
	}
	if (is_valid_operator(args) == FALSE)
	{
		free_array(args);
		mini->exit_code = 2;
		return (1);
	}
	return (0);
}

static int	prepare_tokens(t_mini *mini, t_token **tokens)
{
	int		err_code;
	char	**args;

	args = arg_split(mini->input);
	if (args == NULL)
	{
		error_arg_split(mini);
		return (1);
	}
	if (validate_operators(mini, args) == 1)
		return (1);
	if (process_tokens(mini, args, tokens) == 1)
		return (1);
	if (expander(mini, tokens, NULL, &err_code) == 1)
	{
		expander_error(mini, &err_code);
		return (1);
	}
	assign_type_argument(*tokens);
	return (0);
}

static t_command	*build_commands(t_mini *mini, t_token **tokens)
{
	if (!merge_args(tokens))
	{
		error_merge_args(mini);
		return (NULL);
	}
	mini->cmds = split_pipe(*tokens, NULL, NULL, 0);
	if (!mini->cmds)
	{
		error_split_pipe(mini);
		return (NULL);
	}
	free_token(*tokens);
	return (mini->cmds);
}

t_command	*parsing(t_mini *mini)
{
	t_token	*tokens;

	tokens = NULL;
	if (prepare_tokens(mini, &tokens) == 1)
	{
		free_token_argument(tokens);
		free_token(tokens);
		return (NULL);
	}
	mini->cmds = build_commands(mini, &tokens);
	if (mini->cmds == NULL)
	{
		free_token_argument(tokens);
		free_token(tokens);
	}
	return (mini->cmds);
}
