/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:51:21 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/22 21:34:58 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_list(t_mini *mini)
{
	mini->tokens = create_list(mini->args);
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
		return (1);
	}
	return (0);
}

static int	check_operator(t_mini *mini)
{
	if (is_even_quotes(mini->args) == FALSE)
	{
		mini->exit_code = 1;
		free_array(mini->args);
		return (1);
	}
	if (is_valid_operator(mini->args) == FALSE)
	{
		mini->exit_code = 2;
		free_array(mini->args);
		return (1);
	}
	return (0);
}

t_command	*parsing(t_mini *mini)
{
	int i=0;
	mini->args = arg_split(mini->input);
	while (mini->args[i] != NULL)
	{
		printf("%s\n", mini->args[i]);
		i++;
	}
	if (mini->args == NULL)
		error_arg_split(mini);
	if (check_operator(mini) == 1)
		return (NULL);
	if (handle_list(mini) == 1)
		return (NULL);
	is_tilde(mini);
	expander(mini);
	assign_type_argument(mini->tokens);
	if (merge_args(&mini->tokens) == FALSE)
		error_merge_args(mini);
	mini->cmds = split_pipe(mini->tokens, NULL, NULL, 0);
	if (mini->cmds == NULL)
		error_split_pipe(mini);
	free_token(mini->tokens);
	return (mini->cmds);
}
