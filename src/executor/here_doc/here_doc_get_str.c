/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_get_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 19:29:57 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/16 19:50:42 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*read_line(t_mini *mini, int here_doc_fd, char *new, char *limiter)
{
	char	*str;

	write(1, "> ", 2);
	str = get_next_line(0);
	if (signal_received)
		get_str_error(mini, here_doc_fd, new, limiter);
	return (str);
}

static int	expand(t_mini *mini, t_command *current, char *limiter, char **str)
{
	if ((ft_strncmp(limiter, *str, ft_strlen(limiter) + 1)) == 0)
	{
		free(*str);
		return (1);
	}
	if (current->limiter_quotes == NO_QUOTES)
		*str = expand_shell_vars(*str, mini);
	return (0);
}

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

char	*add_line_return(char *source, t_mini *mini)
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
		write(STDERR_FILENO, "add_line_return :", 17);
		write(STDERR_FILENO, "memory allocation failed\n", 25);
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

char	*get_str(char *limiter, t_mini *mini, char *str, t_command *current)
{
	char	*new;

	new = NULL;
	while (1)
	{
		str = read_line(mini, current->here_doc_fd, new, limiter);
		if (str == NULL)
		{
			write(1, "\nHere doc : delimited by end of file\n", 37);
			return (new);
		}
		if (expand(mini, current, limiter, &str) == 1)
			break ;
		new = join_strings(new, str, ft_strlen(new), ft_strlen(str));
		free(str);
		if (new == NULL)
		{
			here_doc_error("join_strings: memory allocation failed", NULL);
			get_str_error(mini, current->here_doc_fd, new, limiter);
			exit (EXIT_FAILURE);
		}
	}
	return (new);
}
