/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:04:18 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/23 13:40:26 by ncontin          ###   ########.fr       */
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
static void	advance_token(t_token **tokens, t_token **current)
{
	*current = *tokens;
	*tokens = (*tokens)->next;
}

static void	handle_expandable_token(t_mini *mini, t_token **tokens,
		t_token **current)
{
	(*tokens)->argument = expand_special_vars((*tokens)->argument, mini);
	if ((*tokens)->argument == NULL)
		replace_tokens(tokens);
	else
	{
		split_words(mini, tokens);
		advance_token(tokens, current);
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
			advance_token(&tokens, &current);
		else if (tokens->quotes != SINGLE && tokens->argument != NULL)
			handle_expandable_token(mini, &tokens, &current);
		else
			advance_token(&tokens, &current);
	}
	while (current->prev != NULL)
		current = current->prev;
	mini->tokens = current;
}
