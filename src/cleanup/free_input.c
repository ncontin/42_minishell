/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 19:00:54 by ncontin           #+#    #+#             */
/*   Updated: 2025/03/26 17:30:29 by aroullea         ###   ########.fr       */
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
	free(mini->input);
	mini->input = NULL;
}
