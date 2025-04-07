/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:38:28 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/07 15:26:18 by aroullea         ###   ########.fr       */
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
		{
			while (current->argv[i])
			{
				free(current->argv[i]);
				current->argv[i] = NULL;
				i++;
			}
			i = 0;
		}
		free(current->argv);
		current->argv = NULL;
		while (i < current->nb_operator)
		{
			free(current->file[i]);
			i++;
		}
		free(current->file);
		i = 0;
		free(current->operator);
		free(current);
		current = cmds;
	}
}
