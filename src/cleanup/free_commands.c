/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:38:28 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/07 18:57:11 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_commands(t_command *cmds)
{
	t_command	*current;
	int			i;

	i = 0;
	current = cmds;
	while (current != NULL)
	{
		cmds = cmds->next;
		if (current->argv != NULL)
			free_array(current->argv);
		while (i < current->nb_operator)
		{
			free(current->file[i]);
			i++;
		}
		i = 0;
		free(current->file);
		free(current->operator);
		free(current);
		current = cmds;
	}
}
