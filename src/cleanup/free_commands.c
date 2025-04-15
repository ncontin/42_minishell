/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:38:28 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/15 23:45:14 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_commands(t_command *cmds)
{
	t_command	*current;
	int			i;

	current = cmds;
	while (current != NULL)
	{
		cmds = cmds->next;
		if (current->argv != NULL)
			free_array(current->argv);
		i = 0;
		while (i < current->nb_operator)
		{
			free(current->file[i]);
			i++;
		}
		i = 0;
		if (current->here_doc_fd != -1)
			close(current->here_doc_fd);
		free(current->file);
		free(current->arg_quotes);
		free(current->operator);
		free(current);
		current = cmds;
	}
}
