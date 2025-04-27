/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:31:05 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/27 09:31:55 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_first_word(t_token *current, char **split_words)
{
	free(current->argument);
	current->argument = ft_strdup(split_words[0]);
	if (!current->argument)
	{
		free_array(split_words);
		return (1);
	}
	current->quotes = NO_QUOTES;
	current->linked = FALSE;
	current->operator = NONE;
	return (0);
}

static int	handle_single_word(t_token *current, char **split_words)
{
	if (handle_first_word(current, split_words) == 1)
		return (1);
	free_array(split_words);
	return (0);
}

static int	handle_words(t_token *current, char **split_words, t_token *next_og)
{
	int	i;

	i = 1;
	if (handle_first_word(current, split_words) == 1)
		return (1);
	while (split_words[i])
	{
		if (add_new_token(current, split_words[i], next_og) == 1)
		{
			free_array(split_words);
			return (1);
		}
		current = current->next;
		i++;
	}
	free_array(split_words);
	return (0);
}

static void	handle_empty_result(t_token **current)
{
	(*current)->prev->next = (*current)->next;
	if ((*current)->next)
		(*current)->next->prev = (*current)->prev;
	free((*current)->argument);
	free(*current);
	*current = NULL;
}

int	split_words(t_mini *mini, t_token **tokens)
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
			&& mini->expanded == 1 && current->linked == FALSE)
		{
			split_words = ft_split(current->argument, ' ');
			if (split_words == NULL)
				return (1);
			array_size = get_array_size(split_words);
			if (array_size > 1)
			{
				if (handle_words(current, split_words, next_og) == 1)
					return (1);
			}
			else if (array_size == 1)
			{
				if (handle_single_word(current, split_words) == 1)
					return (1);
			}
			else if (array_size == 0)
				handle_empty_result(&current);
		}
		current = next_og;
	}
	return (0);
}
