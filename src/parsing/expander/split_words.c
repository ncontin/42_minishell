/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:31:05 by ncontin           #+#    #+#             */
/*   Updated: 2025/05/01 07:08:21 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_first_word(t_token *current, char **split_words)
{
	char	*str;

	str = ft_strdup(split_words[0]);
	if (str == NULL)
		return (1);
	if (current->prev != NULL && current->prev->linked == TRUE
		&& ft_isspace(current->argument[0]))
		current->prev->linked = FALSE;
	else if (current->prev != NULL && current->prev->linked == TRUE
		&& !ft_isspace(current->argument[0]))
		current->prev->linked = TRUE;
	free(current->argument);
	current->argument = str;
	current->quotes = NO_QUOTES;
	current->linked = FALSE;
	current->operator = NONE;
	return (0);
}

static int	handle_words(t_token *current, char **split_words, t_token *next_og)
{
	int		i;
	t_bool	link;
	size_t	len;

	i = 1;
	link = FALSE;
	len = ft_strlen(current->argument);
	if (!ft_isspace(current->argument[len - 1]) && current->linked == TRUE)
		link = TRUE;
	if (handle_first_word(current, split_words) == 1)
		return (1);
	while (split_words[i])
	{
		if (add_new_token(current, split_words[i], next_og) == 1)
			return (1);
		current = current->next;
		i++;
	}
	current->linked = link;
	return (0);
}

static void	handle_empty_result(t_token **current)
{
	(*current)->prev->next = (*current)->next;
	(*current)->prev->linked = FALSE;
	if ((*current)->next)
		(*current)->next->prev = (*current)->prev;
	free((*current)->argument);
	free(*current);
	*current = NULL;
}

static int	process_current(t_token **current, t_token *next_og,
		int *err_code, char **split_words)
{
	int		array_size;

	array_size = get_array_size(split_words);
	if (array_size > 1)
	{
		if ((*current)->prev != NULL && (*current)->prev->operator != NONE)
		{
			*err_code = 2;
			return (1);
		}
		if (handle_words(*current, split_words, next_og) == 1)
			return (1);
	}
	else if (array_size == 1)
	{
		if (handle_first_word(*current, split_words) == 1)
			return (1);
	}
	else if (array_size == 0)
		handle_empty_result(current);
	return (0);
}

int	split_words(t_mini *mini, t_token **tokens, int *err_code)
{
	t_token	*current;
	t_token	*next_og;
	char	**split_words;

	current = *tokens;
	next_og = current->next;
	split_words = NULL;
	if (current->quotes == NO_QUOTES && has_space(current->argument))
	{
		if (mini->expanded == 1)
		{
			split_words = ft_split(current->argument, ' ');
			if (split_words == NULL)
				return (1);
			if (process_current(&current, next_og, err_code, split_words) == 1)
			{
				free_array(split_words);
				return (1);
			}
		}
	}
	free_array(split_words);
	return (0);
}
