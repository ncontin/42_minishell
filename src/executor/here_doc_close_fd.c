/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_close_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:52:47 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/18 18:05:32 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_child_heredoc_fd(t_command *cmds, t_command *current)
{
	t_command	*commands;

	commands = cmds;
	while (commands != NULL)
	{
		if (commands->check_here_doc == TRUE)
		{
			if (current != commands && commands->here_doc_fd != -1)
			{
				close (commands->here_doc_fd);
				commands->here_doc_fd = -1;
			}
		}
		commands = commands->next;
	}
}

void	close_parent_heredoc_fd(t_command *current)
{
	t_command	*commands;

	commands = current->prev;
	while (commands != NULL)
	{
		if (commands->check_here_doc == TRUE && commands->here_doc_fd != -1)
		{
			close (commands->here_doc_fd);
			commands->here_doc_fd = -1;
		}
		commands = commands->prev;
	}
}
