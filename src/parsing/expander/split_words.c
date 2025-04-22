/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:31:05 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/18 18:26:38 by ncontin          ###   ########.fr       */
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

static void	handle_single_word(t_token *current, char **split_words)
{
	free(current->argument);
	current->argument = ft_strdup(split_words[0]);
	if (!current->argument)
	{
		free_array(split_words);
		return ;
	}
	free_array(split_words);
}

static void	handle_multiple_words(t_token *current, char **split_words,
		t_token *next_og)
{
	int	i;

	i = 1;
	free(current->argument);
	current->argument = ft_strdup(split_words[0]);
	if (!current->argument)
	{
		free_array(split_words);
		return ;
	}
	while (split_words[i])
	{
		add_new_token(current, split_words[i], next_og);
		current = current->next;
		i++;
	}
	free_array(split_words);
}

static void	handle_empty_result(t_token *current)
{
	current->prev->next = current->next;
	if (current->next)
		current->next->prev = current->prev;
	free(current->argument);
	free(current);
}

void	split_words(t_mini *mini, t_token **tokens)
{
	t_token	*current;
	t_token	*next_og;
	char	**split_words;
	int		array_size;

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
				handle_multiple_words(current, split_words, next_og);
			else if (array_size == 1)
				handle_single_word(current, split_words);
			else if (array_size == 0)
				handle_empty_result(current);
			mini->expanded = 0;
		}
		current = next_og;
	}
}
