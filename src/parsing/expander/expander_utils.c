/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:07:36 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/24 16:52:37 by ncontin          ###   ########.fr       */
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

void	handle_nl_expand(t_token **tokens)
{
	free((*tokens)->argument);
	if (ft_strncmp("\\n", (*tokens)->next->argument, 2) == 0)
		(*tokens)->argument = ft_strdup("\n");
	else if (ft_strncmp("\\r", (*tokens)->next->argument, 2) == 0)
		(*tokens)->argument = ft_strdup("\r");
	else if (ft_strncmp("\\t", (*tokens)->next->argument, 2) == 0)
		(*tokens)->argument = ft_strdup("\t");
	free((*tokens)->next->argument);
	(*tokens)->next->argument = NULL;
}
