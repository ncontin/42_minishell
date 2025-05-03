/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:04:18 by ncontin           #+#    #+#             */
/*   Updated: 2025/05/03 09:13:03 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_special_vars(char *arg, t_mini *mini, int *err_code)
{
	arg = expand_shell_vars(arg, mini, err_code);
	if (*err_code == 1 || arg == NULL)
		return (NULL);
	arg = expand_exit_status(arg, mini);
	if (arg == NULL)
		*err_code = 1;
	return (arg);
}

static int	expandable_token(t_mini *mini, t_token **tokens, t_token **current,
		int *err_code)
{
	*err_code = 0;
	(*tokens)->argument = expand_special_vars((*tokens)->argument, mini,
			err_code);
	if (*err_code == 1)
		return (1);
	if ((*tokens)->argument == NULL)
		replace_tokens(tokens);
	else
	{
		if (split_words(mini, tokens, err_code) == 1)
			return (1);
		advance_token(tokens, current);
	}
	return (0);
}

static int	handle_dollar(t_token **tokens, t_token **current)
{
	if (is_nl_char(tokens))
	{
		if (handle_nl_expand(tokens) == 1)
			return (1);
	}
	advance_token(tokens, current);
	return (0);
}

int	expander(t_mini *mini, t_token *tokens, t_token *current, int *err_code)
{
	while (tokens != NULL)
	{
		if (is_dollar(&tokens) && tokens->next && tokens->next->argument)
		{
			if (handle_dollar(&tokens, &current) == 1)
				return (1);
		}
		else if (tokens->prev != NULL && tokens->prev->operator == HEREDOC)
			advance_token(&tokens, &current);
		else if (tokens->quotes != SINGLE && tokens->argument != NULL)
		{
			if (expandable_token(mini, &tokens, &current, err_code) == 1)
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
