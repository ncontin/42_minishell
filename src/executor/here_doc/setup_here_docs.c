/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_here_docs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:17:22 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/16 19:57:08 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parent(t_mini *mini, t_command *current, pid_t pid, int hd_pipe[2])
{
	int	status;
	int	sig;

	status = -1;
	if (waitpid(pid, &status, 0) == -1)
	{
		write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
		write(STDERR_FILENO, "\n", 1);
	}
	close(hd_pipe[1]);
	current->here_doc_fd = hd_pipe[0];
	if (status)
	{
		if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			mini->exit_code = 128 + sig;
		}
		else if (WIFEXITED(status))
			mini->exit_code = WEXITSTATUS(status);
	}
	if (mini->exit_code > 0)
		return (1);
	return (0);
}

static void	children(t_mini *mini, t_command *current, int i, int hd_pipe)
{
	char	*str;
	char	*limiter;

	str = NULL;
	limiter = NULL;
	here_doc_child_signal();
	current->here_doc_fd = hd_pipe;
	limiter = add_line_return(current->file[i], mini);
	if (limiter == NULL)
	{
		close(hd_pipe);
		free_exit(mini);
		exit (EXIT_FAILURE);
	}
	str = get_str(limiter, mini, NULL, current);
	if (write(hd_pipe, str, ft_strlen(str)) == -1)
	{
		here_doc_exit(mini, limiter, str, &hd_pipe);
		exit (EXIT_FAILURE);
	}
	here_doc_exit(mini, limiter, str, &hd_pipe);
	exit (EXIT_SUCCESS);
}

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
		children(mini, current, i, here_doc_pipe[1]);
	}
	else
		if (parent(mini, current, pid, here_doc_pipe) == 1)
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
