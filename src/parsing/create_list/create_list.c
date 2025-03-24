/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:27:12 by aroullea          #+#    #+#             */
/*   Updated: 2025/03/24 15:09:24 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	str_count(t_bool *quotes, t_bool *in_word)
{
	*quotes = !(*quotes);
	*in_word = !(*in_word);
	if (*quotes == FALSE)
		return (1);
	return (0);
}

static int	is_multi_strings(char *args, int i, t_bool dquotes, t_bool squotes)
{
	int		nb_strings;
	t_bool	no_quotes;
	t_bool	in_word;

	nb_strings = 0;
	no_quotes = FALSE;
	in_word = FALSE;
	while (args[i] != '\0')
	{
		if (args[i] == '\'' && !dquotes)
		{
			if (args[i + 1] == '\'' && in_word == FALSE)
				i++;
			else
			{
				no_quotes = FALSE;
				nb_strings += str_count(&squotes, &in_word);
			}
		}
		else if (args[i] == '"' && !squotes)
		{
			if (args[i + 1] == '"' && in_word == FALSE)
				i++;
			else
			{
				no_quotes = FALSE;
				nb_strings += str_count(&dquotes, &in_word);
			}
		}
		else if (no_quotes == FALSE && !dquotes && !squotes)
		{
			no_quotes = TRUE;
			nb_strings++;
		}
		i++;
	}
	return (nb_strings);
}

static t_token	*new_list(char *args, int nb_strings, t_token *head)
{
	t_token	*current;
	int		size;

	current = NULL;
	if (nb_strings == 1)
	{
		current = init_new_list(head);
		if (current == NULL)
			return (NULL);
		check_quotes(args, current);
		size = get_size(args);
		current->argument = rm_quotes(args, size);
		if (current->argument == NULL)
		{
			write(2, "Memory allocation failed to create arg\n", 39);
			free_token(head);
			return (NULL);
		}
		lst_add_new(&head, current);
	}
	else
		multi_str(args, nb_strings, &head);
	return (head);
}

static void	printouff(t_token *head)
{
	t_token	*current;

	current = head;
	while (current != NULL)
	{
		printf("%s\n", current->argument);
		printf("%d\n", current->quotes);
		printf("%d\n", current->linked);
		current = current->next;
	}
}

t_token	*create_list(char **tokens)
{
	int		i;
	int		nb_strings;
	t_token	*head;

	i = 0;
	head = NULL;
	while (tokens[i] != NULL)
	{
		nb_strings = is_multi_strings(tokens[i], 0, FALSE, FALSE);
		head = new_list(tokens[i], nb_strings, head);
		if (head == NULL)
		{
			free_array(tokens);
			return (NULL);
		}
		i++;
	}
	printouff(head);
	return (head);
}
