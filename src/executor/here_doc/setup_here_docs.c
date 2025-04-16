/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_here_docs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:17:22 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/16 12:48:45 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_strings(char *s1, char const *s2, size_t k, size_t l)
{
	size_t	i;
	char	*str;

	i = 0;
	str = malloc(sizeof(char) * (k + l + 1));
	if (str == NULL)
	{
		free(s1);
		return (NULL);
	}
	while (i < k)
	{
		str[i] = s1[i];
		i++;
	}
	while (i < k + l)
	{
		str[i] = s2[i - k];
		i++;
	}
	str[k + l] = '\0';
	free(s1);
	return (str);
}

static char	*get_str(char *limiter, t_mini *mini, char *str, t_command *current)
{
	char	*new;
	t_bool	is_str_null;

	is_str_null = FALSE;
	new = NULL;
	while (!signal_received)
	{
		write(1, "> ", 2);
		str = get_next_line(0);
		if (signal_received)
			break ;
		if (str != NULL)
			if ((ft_strncmp(limiter, str, ft_strlen(limiter) + 1)) == 0)
				break ;
		if (current->limiter_quotes == NO_QUOTES)
		{
			is_str_null = (str == NULL);
			str = expand_shell_vars(str, mini);
		}
		new = join_strings(new, str, ft_strlen(new), ft_strlen(str));
		if (new == NULL)
			return (NULL);
		if (is_str_null == TRUE)
		{
			write(1, "\nHere doc : delimited by end of file\n", 37);
			return (new);
		}
		free(str);
	}
	if (signal_received)
	{
		close(current->here_doc_fd);
		if (new != NULL)
			free(new);
		free(limiter);
		free_exit(mini);
		exit (130);
	}
	free(str);
	return (new);
}

static char *add_line_return(char *source, t_mini *mini)
{
	char	*limiter;
	size_t	size;
	size_t	i;

	(void)mini;
	i = 0;
	size = ft_strlen(source);
	limiter = (char *)malloc(sizeof(char) * size + 2);
	if (limiter == NULL)
	{
		write(STDERR_FILENO, "here_doc allocation error\n", 26);
		return (NULL);
	}
	while (i < size)
	{
		limiter[i] = source[i];
		i++;
	}
	limiter[i] = '\n';
	limiter[i + 1] = '\0';
	i++;
	return (limiter);
}

static int	read_here_doc(t_mini *mini, t_command *current, int i)
{
	char				*limiter;
	int					here_doc_pipe[2];
	pid_t				pid;
	char				*str;
	int					status;

	if (current->here_doc_fd != -1)
		close(current->here_doc_fd);
	here_doc_parent_signal();
	if (pipe(here_doc_pipe) == -1)
	{
		write(STDERR_FILENO, strerror(errno), errno);
		return (1);
	}
	pid = fork();
	if (pid == -1)
	{
		close(here_doc_pipe[0]);
		close(here_doc_pipe[1]);
		write(STDERR_FILENO, strerror(errno), errno);
		return (1);
	}
	else if (pid == 0)
	{
		here_doc_child_signal();
		current->here_doc_fd = here_doc_pipe[1];
		close(here_doc_pipe[0]);
		limiter = add_line_return(current->file[i], mini);
		if (limiter == NULL)
		{
			close(here_doc_pipe[1]);
			free_exit(mini);
			exit (EXIT_FAILURE);
		}
		str = get_str(limiter, mini, NULL, current);
		write(here_doc_pipe[1], str, ft_strlen(str));
		free(limiter);
		free(str);
		free_exit(mini);
		close(here_doc_pipe[1]);
		exit (EXIT_SUCCESS);
	}
	else
	{
		waitpid(pid, &status, 0);
		close(here_doc_pipe[1]);
		current->here_doc_fd = here_doc_pipe[0];
		if (WIFEXITED(status))
			mini->exit_code = WEXITSTATUS(status);
		if (mini->exit_code > 0)
			return (1);
	}
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
				if (read_here_doc(mini, current, i) == 1)
					return (1);
			}
			i++;
		}
		i = 0;
		current = current->next;
	}
	return (0);
}
