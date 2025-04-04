/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:11:42 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/04 17:36:12 by aroullea         ###   ########.fr       */
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

static char	*get_str(char *limiter, t_mini *mini, char *str)
{
	char	*new;

	new = NULL;
	(void)mini;
	while (1)
	{
		write(1, "> ", 2);
		str = get_next_line(0);
		if (str != NULL)
			if ((ft_strncmp(limiter, str, ft_strlen(limiter) + 1)) == 0)
				break ;
		new = join_strings(new, str, ft_strlen(new), ft_strlen(str));
		if (new == NULL)
		{
			//data_free(fd, str, limiter, data);
			//handle_error("\nHere doc : memory allocation failed", 1, NULL);
		}
		if (str == NULL)
		{
			write(1, "\nHere doc : delimited by end of file\n", 37);
			return (new);
		}
		free(str);
	}
	free(str);
	return (new);
}

static char	*add_line_return(char *source, t_mini *mini, int *fd)
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
		write(2, "here_doc error\n", 15);
		close(*fd);
	}
	while (i < size)
	{
		limiter[i] = source[i];
		i++;
	}
	limiter[i] = '\n';
	limiter[i + 1] = '\0';
	return (limiter);
}

void	setup_here_doc(t_command *current, t_mini *mini)
{
	char	*dest;
	char	*limiter;

	if (pipe(current->pipe_fd) == -1)
		free_all(mini);
	limiter = add_line_return(current->file, mini, current->pipe_fd);
	dest = get_str(limiter, mini, NULL);
	if (write(current->pipe_fd[1], dest, ft_strlen(dest)) == -1)
	{
		write(2, "here_doc error\n", 15);
		free_all(mini);
		free(dest);
		free(limiter);
	}
	if (dup2(current->pipe_fd[1], STDIN_FILENO) == -1)
	{
		write(2, "dup2 error\n", 11);
		free_all(mini);
		free(dest);
		free(limiter);
	}
	close(current->pipe_fd[0]);
	close(current->pipe_fd[1]);
	free_all(mini);
	free(dest);
	free(limiter);
	exit(EXIT_SUCCESS);
}
