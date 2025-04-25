/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:04:18 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/25 12:07:30 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_expandable_token(t_mini *mini, t_token **tokens,
		t_token **current)
{
	int	err_code;

	err_code = 0;
	(*tokens)->argument = expand_special_vars((*tokens)->argument, mini, &err_code);
	if (err_code == 1)
		return (1);
	if ((*tokens)->argument == NULL)
		replace_tokens(tokens);
	else
	{
		split_words(mini, tokens);
		advance_token(tokens, current);
	}
	return (0);
}

int	expander(t_mini *mini)
{
	t_token	*tokens;
	t_token	*current;

	tokens = mini->tokens;
	while (tokens != NULL)
	{
		if (is_dollar(&tokens) && tokens->next && tokens->next->argument)
		{
			if (is_nl_char(&tokens))
			{
				if (handle_nl_expand(&tokens) == 1)
					return (1);
			}
			advance_token(&tokens, &current);
		}
		else if (tokens->prev != NULL && tokens->prev->operator == HEREDOC)
			advance_token(&tokens, &current);
		else if (tokens->quotes != SINGLE && tokens->argument != NULL)
		{
			if (handle_expandable_token(mini, &tokens, &current) == 1)
				return (1);
		}
		else
			advance_token(&tokens, &current);
	}
	while (current->prev != NULL)
		current = current->prev;
	mini->tokens = current;
	return (0);
}
