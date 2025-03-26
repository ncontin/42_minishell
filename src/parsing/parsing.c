/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:51:21 by aroullea          #+#    #+#             */
/*   Updated: 2025/03/26 18:19:26 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(t_mini *mini)
{
	int		i;
	t_bool	even_quotes;

	i = 0;
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
	if (is_builtin(mini->args[0]))
		execute_builtin(mini);
	free_token(mini->tokens);
}
