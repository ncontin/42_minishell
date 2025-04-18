/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:04:18 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/18 13:24:20 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_special_vars(char *arg, t_mini *mini)
{
	arg = expand_exit_status(arg, mini);
	arg = expand_shell_vars(arg, mini);
	return (arg);
}

static void	replace_tokens(t_token **tokens)
{
	t_token	*current;

	current = *tokens;
	if (current->prev == NULL && current->next == NULL)
		return ;
	if (current->prev == NULL)
	{
		current->next->prev = NULL;
		*tokens = (*tokens)->next;
		free(current);
	}
	else if (current->next == NULL)
	{
		current->prev->next = NULL;
		*tokens = (*tokens)->prev;
		free(current);
	}
	else
	{
		current->prev->next = current->next;
		current->next->prev = current->prev;
		*tokens = (*tokens)->next;
		free(current);
	}
}

void	expander(t_mini *mini)
{
	t_token	*tokens;
	t_token	*current;

	tokens = mini->tokens;
	while (tokens != NULL)
	{
		if (tokens->prev != NULL && tokens->prev->operator== HEREDOC)
		{
			current = tokens;
			tokens = tokens->next;
		}
		else if (tokens->quotes != SINGLE && tokens->argument != NULL)
		{
			tokens->argument = expand_special_vars(tokens->argument, mini);
			if (tokens->argument == NULL)
				replace_tokens(&tokens);
			else
			{
				split_words(mini, &tokens);
				current = tokens;
				tokens = tokens->next;
			}
		}
		else
		{
			current = tokens;
			tokens = tokens->next;
		}
	}
	while (current->prev != NULL)
		current = current->prev;
	mini->tokens = current;
}
