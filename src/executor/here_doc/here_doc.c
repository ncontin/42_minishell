/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:11:42 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/13 19:37:01 by aroullea         ###   ########.fr       */
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
		if (mini->cmds->limiter_quotes == NO_QUOTES)
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

void	setup_here_doc(t_command *current, t_mini *mini, int *j)
{
	char	*limiter;
	char	*str;
	int		i;
	int		tmp_fd;

	i = *j;
	here_doc_signal();
	limiter = add_line_return(current->file[i], mini, current->pipe_fd);
	str = get_str(limiter, mini, NULL);
	tmp_fd = open("tmp_file", O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (tmp_fd == -1)
		write(2, "here_doc : open error\n", 21);
	write(tmp_fd, str, ft_strlen(str));
	close(tmp_fd);
	tmp_fd = open("tmp_file", O_RDONLY);
	if (tmp_fd == -1)
		write(2, "here_doc : open error\n", 21);
	if (dup2(tmp_fd, STDIN_FILENO) == -1)
		write(2, "here_doc : dup2 error\n", 21);
	close(tmp_fd);
	unlink("tmp_file");
	free(limiter);
	free(str);
}
