/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:16:20 by aroullea          #+#    #+#             */
/*   Updated: 2025/05/04 09:46:31 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	replace_arg(t_token *current, size_t len, t_mini *mini)
{
	size_t	i;
	char	*new;

	i = 0;
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (new == NULL)
	{
		mini->exit_code = 2;
		write(STDERR_FILENO, "memory allocation failed in check dollar\n", 41);
		return (1);
	}
	while (i < len)
	{
		new[i] = current->argument[i];
		i++;
	}
	new[i] = '\0';
	free(current->argument);
	current->argument = new;
	return (0);
}

static void	add_token(t_token *new, t_token *current)
{
	current->next->prev = new;
	new->next = current->next;
	current->next = new;
	new->prev = current;
	new->quotes = NO_QUOTES;
	new->linked = TRUE;
	new->hd_expand = TRUE;
	new->operator = NONE;
}

static int	new_token(t_token *current, t_mini *mini)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (new == NULL)
	{
		mini->exit_code = 2;
		write(STDERR_FILENO, "memory allocation failed in check dollar\n", 41);
		return (1);
	}
	new->argument = (char *)malloc(sizeof(char) * 2);
	if (new->argument == NULL)
	{
		free(new);
		mini->exit_code = 2;
		write(STDERR_FILENO, "memory allocation failed in check dollar\n", 41);
		return (1);
	}
	new->argument[0] = '$';
	new->argument[1] = '\0';
	add_token(new, current);
	return (0);
}

int	check_dollar(t_mini *mini, t_token *tokens)
{
	t_token		*current;
	size_t		len;
	t_quotes	quotes;

	current = tokens;
	while (current != NULL)
	{
		quotes = current->quotes;
		if (current->argument && current->linked && quotes == NO_QUOTES)
		{
			len = ft_strlen(current->argument) - 1;
			if (current->argument[len] == '$')
			{
				if (replace_arg(current, len, mini) == 1)
					return (1);
				if (new_token(current, mini) == 1)
					return (1);
				current = current->next;
			}
		}
		current = current->next;
	}
	return (0);
}
