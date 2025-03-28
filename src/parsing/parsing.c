/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:51:21 by aroullea          #+#    #+#             */
/*   Updated: 2025/03/28 14:23:45 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(t_mini *mini)
{
	t_bool	even_quotes;

	mini->args = arg_split(mini->input);
	if (mini->args == NULL)
		return ;
	even_quotes = is_even_quotes(mini->args);
	if (even_quotes == FALSE)
		return ;
	mini->tokens = create_list(mini->args);
	if (mini->tokens == NULL)
		return ;
	assign_operator(mini->tokens);
	if (is_valid_token(mini->tokens) == FALSE)
	{
		free_token(mini->tokens);
		return ;
	}
	assign_type_argument(mini->tokens);
	get_env_argument(mini);
	t_token  *current;
	current = mini->tokens;
	while (current != NULL)
	{
		printf("%s\n", current->argument);
		current = current->next;
	}
	if (is_builtin(mini->args[0]))
		execute_builtin(mini);
	free_token(mini->tokens);
}
