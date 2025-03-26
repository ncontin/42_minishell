/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:51:21 by aroullea          #+#    #+#             */
/*   Updated: 2025/03/26 17:43:15 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(t_mini *mini)
{
	int		i;
	t_bool	even_quotes;
	t_token	*lst_tokens;

	i = 0;
	mini->args = arg_split(mini->input);
	if (mini->args == NULL)
		return ;
	even_quotes = is_even_quotes(mini->args);
	if (even_quotes == FALSE)
		return ;
	lst_tokens = create_list(mini->args);
	if (lst_tokens == NULL)
		return ;
	assign_operator(lst_tokens);
	if (is_valid_token(lst_tokens) == FALSE)
	{
		free_token(lst_tokens);
		return ;
	}
	if (is_builtin(mini->args[0]))
		execute_builtin(mini);
}
