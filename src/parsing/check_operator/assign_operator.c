/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_operator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:57:16 by aroullea          #+#    #+#             */
/*   Updated: 2025/03/26 16:54:01 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	operator_type(t_token *current)
{
	if (current->argument == NULL)
		return ;
	if (ft_strncmp(current->argument, ">", 2) == 0)
		current->operator = OUTPUT;
	else if (ft_strncmp(current->argument, "<", 2) == 0)
		current->operator = INPUT;
	else if (ft_strncmp(current->argument, "|", 2) == 0)
		current->operator = PIPE;
	else if (ft_strncmp (current->argument, ">>", 3) == 0)
		current->operator = APPEND;
	else if (ft_strncmp (current->argument, "<<", 3) == 0)
		current->operator = HEREDOC;
}

/*void	printouf(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current != NULL)
	{
		printf("%s\n", current->argument);
		printf("%d\n", current->quotes);
		printf("%d\n", current->linked);
		printf("%d\n", current->operator);
		current = current->next;
	}
}*/

void	assign_operator(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current != NULL)
	{
		if (current->quotes == NO_QUOTES)
			operator_type(current);
		current = current->next;
	}
	//printouf(tokens);
}
