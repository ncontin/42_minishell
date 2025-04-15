/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_here_docs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:17:22 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/15 16:38:31 by aroullea         ###   ########.fr       */
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
		write(2, "here_doc error\n", 15);
	while (i < size)
	{
		limiter[i] = source[i];
		i++;
	}
	limiter[i] = '\n';
	limiter[i + 1] = '\0';
	return (limiter);
}

static int	read_here_doc(t_mini *mini, t_command *current, int i, char **str)
{
	char	*limiter;

	here_doc_signal();
	limiter = add_line_return(current->file[i], mini);
	*str = get_str(limiter, mini, NULL, current);
	free(limiter);
	return (0);
}

static void	handle_pipe_here_doc(t_mini *mini, t_command *current, char *str)
{
	int		here_doc_pipe[2];
	
	(void)mini;
	pipe(here_doc_pipe);
	write(here_doc_pipe[1], str, ft_strlen(str));
	close(here_doc_pipe[1]);
	current->here_doc_fd = here_doc_pipe[0];
	free(str);
}

int	setup_here_docs(t_mini *mini)
{
	t_command	*current;
	int			i;
	t_bool		find;
	char		*str;

	i = 0;
	find = FALSE;
	str = NULL;
	current = mini->cmds;
	while (current != NULL)
	{
		while (i < current->nb_operator)
		{
			if (current->operator[i] == HEREDOC)
			{
				find = TRUE;
				if (str != NULL)
				{
					free(str);
					str = NULL;
				}
				if (read_here_doc(mini, current, i, &str) == 1)
					return (1);
			}
			i++;
		}
		if (find == TRUE)
			handle_pipe_here_doc(mini, current, str);
		i = 0;
		current = current->next;
		find = FALSE;
		str = NULL;
	}
	return (0);
}
