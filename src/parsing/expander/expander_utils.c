/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:07:36 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/24 23:05:05 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_special_vars(char *arg, t_mini *mini)
{
	arg = expand_exit_status(arg, mini);
	arg = expand_shell_vars(arg, mini);
	return (arg);
}

void	replace_tokens(t_token **tokens)
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

void	advance_token(t_token **tokens, t_token **current)
{
	*current = *tokens;
	*tokens = (*tokens)->next;
}

static void	remove_next_token(t_token **current)
{
	t_token	*next;

	next = (*current)->next;
	if ((*current)->prev != NULL)
	{
		(*current)->prev->next = (*current)->next;
		(*current)->next->prev = (*current)->prev;
	}
	else
		(*current)->next->prev = NULL;
	free((*current)->argument);
	free(*current);
	*current = next;
}

int	handle_nl_expand(t_token **tokens)
{
	if (ft_strncmp("\\n", (*tokens)->next->argument, 2) == 0)
	{
		free((*tokens)->next->argument);
		(*tokens)->next->argument = ft_strdup("\n");
		//(*tokens)->next->argument = NULL;
		if ((*tokens)->next->argument == NULL)
		{
			write(STDERR_FILENO, "memory allocation failed in nl_expand\n", 38);
			return (1);
		}
	}
	else if (ft_strncmp("\\r", (*tokens)->next->argument, 2) == 0)
	{
		free((*tokens)->next->argument);
		(*tokens)->next->argument = ft_strdup("\r");
		if ((*tokens)->next->argument == NULL)
		{
			write(STDERR_FILENO, "memory allocation failed in nl_expand\n", 38);
			return (1);
		}
	}
	else if (ft_strncmp("\\t", (*tokens)->next->argument, 2) == 0)
	{
		free((*tokens)->next->argument);
		(*tokens)->next->argument = ft_strdup("\t");
		if ((*tokens)->next->argument == NULL)
		{
			write(STDERR_FILENO, "memory allocation failed in nl_expand\n", 38);
			return (1);
		}
	}
	remove_next_token(tokens);
	return (0);
}
