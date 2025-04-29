/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:31:12 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/29 09:33:18 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_msg(char *message, int error)
{
	write(STDERR_FILENO, message, ft_strlen(message) + 1);
	write(STDERR_FILENO, "\n", 1);
	exit(error);
}

void	error_create_list(t_token **tokens, t_token *current)
{
	write(2, "Create_list :", 13);
	write(2, "memory allocation failed to create arg\n", 39);
	if (current != NULL)
		free(current);
	if (*tokens != NULL)
	{
		free_token_argument(*tokens);
		free_token(*tokens);
		*tokens = NULL;
	}
}

void	error_arg_split(t_mini *mini)
{
	mini->exit_code = 2;
	write(STDERR_FILENO, "arg_split :", 11);
	write(STDERR_FILENO, "memory allocation failed\n", 25);
}

void	error_merge_args(t_mini *mini)
{
	mini->exit_code = 2;
	write(STDERR_FILENO, "Merge_args :", 12);
	write(STDERR_FILENO, "memory allocation failed\n", 25);
}

void	error_split_pipe(t_mini *mini)
{
	mini->exit_code = 2;
	write(STDERR_FILENO, "Split_pipe :", 12);
	write(STDERR_FILENO, "memory allocation failed\n", 25);
}
