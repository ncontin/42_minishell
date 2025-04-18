/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:31:05 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/18 13:26:40 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	has_space(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

static int	get_array_size(char **array)
{
	int	counter;

	counter = 0;
	while (array[counter])
		counter++;
	return (counter);
}

static t_token	*create_token(char *arg)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->argument = ft_strdup(arg);
	if (!new_token->argument)
	{
		free(new_token);
		return (NULL);
	}
	new_token->quotes = NO_QUOTES;
	new_token->linked = FALSE;
	new_token->operator= NONE;
	new_token->next = NULL;
	new_token->prev = NULL;
	return (new_token);
}

static void	add_new_token(t_token *token, char *word, t_token *next_og)
{
	t_token	*current;
	t_token	*next;
	t_token	*new;

	new = create_token(word);
	current = token;
	next = token->next;
	current->next = new;
	new->next = next_og;
	new->prev = current;
	if (next_og)
		next_og->prev = new;
}

void	split_words(t_mini *mini, t_token **tokens)
{
	t_token	*current;
	char	**split_words;
	t_token	*next_og;
	char	*trimmed_word;
	int		array_size;
	int		i;

	// word_splitting(t_token **tokens):
	// This function iterates through the token list.
	// If a token has quotes == NO_QUOTES and its argument contains IFS whitespace (e.g.,
	// 		spaces):
	// Use a function similar to ft_split (let's call it ft_split_word) to split the argument string by spaces/tabs/newlines. This split function must discard empty results (e.g.,
	// 	" foo  bar " should split into "foo" and "bar").
	// If the split results in more than one word:
	// Update the current token's argument with the first word.
	// Insert new tokens into the list after the current token for each subsequent word. These new tokens should also have quotes = NO_QUOTES.
	// If the split results in exactly one word (e.g., trimming occurred):
	// Update the current token's argument with that single word.
	// If the split results in zero words (the argument was only whitespace):
	// Remove the current token from the list entirely.
	// This function needs careful handling of pointers while modifying the linked list.
	current = *tokens;
	while (current)
	{
		next_og = current->next;
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
					add_new_token(current, split_words[i], next_og);
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
				current->prev->next = current->next;
				if (current->next)
					current->next->prev = current->prev;
				free(current->argument);
				free(current);
			}
			free_array(split_words);
		}
		current = next_og;
	}
}
