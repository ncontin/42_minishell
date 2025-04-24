/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:04:18 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/24 16:52:30 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (is_dollar(&tokens) && tokens->next && tokens->next->argument)
		{
			if (is_nl_char(&tokens))
				handle_nl_expand(&tokens);
			advance_token(&tokens, &current);
		}
		else if (tokens->prev != NULL && tokens->prev->operator== HEREDOC)
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
