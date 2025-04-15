/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:11:42 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/15 14:25:21 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc_redirection(t_command *current, t_mini *mini)
{
	(void)mini;

	if (dup2(current->here_doc_fd, STDIN_FILENO) == -1)
		write(2, "here_doc : dup2 error\n", 21);
	close(current->here_doc_fd);
	current->here_doc_fd = -1;
	if (current->next != NULL)
	{
		dup2(current->pipe_fd[1], STDOUT_FILENO);
		close(current->pipe_fd[1]);
	}
}
