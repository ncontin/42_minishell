/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_parent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:46:16 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/16 18:15:48 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	here_doc_parent(t_mini *mini, t_command *current, pid_t pid, int hd_pipe[2])
{
	int	status;
	int	sig;

	if (waitpid(pid, &status, 0) == -1)
	{
		write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
		write(STDERR_FILENO, "\n", 1);
	}
	close(hd_pipe[1]);
	current->here_doc_fd = hd_pipe[0];
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		mini->exit_code = 128 + sig;
	}
	else if (WIFEXITED(status))
		mini->exit_code = WEXITSTATUS(status);
	if (mini->exit_code > 0)
		return (1);
	return (0);
}
