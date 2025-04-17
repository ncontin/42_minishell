/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:04:18 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/17 18:04:32 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_special_vars(t_token *token, t_mini *mini)
{
	token->argument = expand_exit_status(token->argument, mini);
	if (!token->argument)
		return (NULL);
	token->argument = expand_shell_vars(token->argument, mini);
	if (!token->argument)
		return (NULL);
	return (token->argument);
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
	char	**split_words;
	char	*trimmed_word;
	int		array_size;
	int		i;
	t_token	*to_remove;

	tokens = mini->tokens;
	mini->expanded = 0;
	while (tokens != NULL)
	{
		if (tokens->prev != NULL && tokens->prev->operator== HEREDOC)
		{
			current = tokens;
			tokens = tokens->next;
		}
		else if (tokens->quotes != SINGLE && tokens->argument != NULL)
		{
			tokens->argument = expand_special_vars(tokens, mini);
			if (tokens->argument == NULL)
				replace_tokens(&tokens);
			else
			{
				current = tokens;
				if (current->quotes == NO_QUOTES && has_space(current->argument)
					&& mini->expanded == 1)
				{
					split_words = ft_split(current->argument, ' ');
					array_size = get_array_size(split_words);
					if (array_size > 1)
					{
						free(current->argument);
						current->argument = ft_strdup(split_words[0]);
						if (!current->argument)
							return ;
						i = 1;
						while (split_words[i])
						{
							add_new_token(current, split_words[i]);
							current = current->next;
							i++;
						}
					}
					else if (array_size == 1)
					{
						trimmed_word = ft_strtrim(current->argument, " ");
						free(current->argument);
						current->argument = ft_strdup(trimmed_word);
						free(trimmed_word);
					}
					else if (array_size == 0)
					{
						to_remove = current;
						t_token *next_token = current->next; // Store next token
						// Unlink the token
						if (current->prev)
							current->prev->next = current->next;
						else
							// Removing the head of the list
							mini->tokens = current->next; // Update list head
						if (current->next)
							current->next->prev = current->prev;
						// Free resources
						free(to_remove->argument); // Free the (empty) argument
						free(to_remove);           // Free the token struct
						tokens = next_token;
						// Set loop iterator to the next token
						free_array(split_words); // Free split result
						continue ;
						// Skip the default tokens = tokens->next at the end
					}
					free_array(split_words);
				}
				tokens = tokens->next; // Advance if token was not removed
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
