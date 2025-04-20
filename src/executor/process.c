/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:52:47 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/18 18:05:32 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(t_command *current, int *prev_fd, t_mini *mini)
{
	char	**envp;

	envp = NULL;
	child_signal();
	if (current->next != NULL && current->next->check_here_doc == FALSE)
	{
		close(current->pipe_fd[0]);
		current->pipe_fd[0] = -1;
	}
	close_child_heredoc_fd(mini->cmds, current);
	duplicate_pipes(current, prev_fd, mini);
	if (current->operator != NONE)
		handle_redirection(current, mini);
	if (get_envp_array(mini->lst_env, &envp) == 1)
	{
		if (*prev_fd != -1)
			close(*prev_fd);
		free_exit(mini);
	}
	execute_cmd(current, envp, mini);
}

void	parent_process(int *prev_fd, t_command *current)
{
	if (*prev_fd != -1)
	{
		close(*prev_fd);
		*prev_fd = -1;
	}
	if (current->next != NULL && current->next->check_here_doc == FALSE)
	{
		close(current->pipe_fd[1]);
		current->pipe_fd[1] = -1;
		*prev_fd = current->pipe_fd[0];
	}
	close_parent_heredoc_fd(current);
}
