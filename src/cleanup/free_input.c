/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 19:00:54 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/01 16:57:34 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_input(t_mini *mini)
{
	if (mini->args)
	{
		free_array(mini->args);
		mini->args = NULL;
	}
	if (mini->input)
	{
		free(mini->input);
		mini->input = NULL;
	}
	if (mini->tokens)
		mini->tokens = NULL;
}
