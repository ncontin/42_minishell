/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:27:12 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/09 15:16:30 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*new_list(char *args, int nb_strings, t_token *head)
{
	t_token	*current;
	int		size;

	current = NULL;
	if (nb_strings == 0 || nb_strings == 1)
	{
		current = init_new_list(head);
		if (current == NULL)
			return (NULL);
		check_quotes(args, current);
		size = get_size(args);
		if (size == 0)
			current->argument = handle_size_zero();
		else
			current->argument = rm_quotes(args, size);
		if (current->argument == NULL)
		{
			msg_and_free(head);
			return (NULL);
		}
		lst_add_new(&head, current);
	}
	else
		multi_str(args, nb_strings, &head, 0);
	return (head);
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
	return (head);
}
