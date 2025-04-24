/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:31:05 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/24 11:46:38 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	(void)mini;
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
			else if (array_size == 1 && !next_og)
				handle_single_word(current, split_words);
			else if (array_size == 0)
				handle_empty_result(current);
		}
		current = next_og;
	}
}
