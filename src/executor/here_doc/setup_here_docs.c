/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_here_docs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:17:22 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/16 17:44:25 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_read_here_doc(int here_doc_pipe[2], int *current_fd)
{
	here_doc_parent_signal();
	here_doc_pipe[0] = -1;
	here_doc_pipe[1] = -1;
	if (*current_fd != -1)
	{
		close(*current_fd);
		*current_fd = -1;
	}
}

static int	read_here_doc(t_mini *mini, t_command *current, int i, pid_t pid)
{
	int		here_doc_pipe[2];

	init_read_here_doc(here_doc_pipe, &current->here_doc_fd);
	if (pipe(here_doc_pipe) == -1)
	{
		here_doc_error(strerror(errno), here_doc_pipe);
		return (1);
	}
	pid = fork();
	if (pid == -1)
	{
		here_doc_error(strerror(errno), here_doc_pipe);
		return (1);
	}
	else if (pid == 0)
	{
		close(here_doc_pipe[0]);
		here_doc_child(mini, current, i, here_doc_pipe[1]);
	}
	else
		if (here_doc_parent(mini, current, pid, here_doc_pipe) == 1)
			return (1);
	return (0);
}

int	setup_here_docs(t_mini *mini)
{
	t_command	*current;
	int			i;

	i = 0;
	current = mini->cmds;
	while (current != NULL)
	{
		while (i < current->nb_operator)
		{
			if (current->operator[i] == HEREDOC)
			{
				if (read_here_doc(mini, current, i, 0) == 1)
					return (1);
			}
			i++;
		}
		i = 0;
		current = current->next;
	}
	return (0);
}
