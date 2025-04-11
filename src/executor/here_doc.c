/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:11:42 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/11 15:50:40 by ncontin          ###   ########.fr       */
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
	while (!signal_received)
	{
		str = readline(">");
		if (str != NULL)
			if ((ft_strncmp(limiter, str, ft_strlen(limiter) + 1)) == 0)
				break ;
		if (mini->cmds->limiter_quotes == NO_QUOTES)
			str = expand_shell_vars(str, mini);
		new = join_strings(new, str, ft_strlen(new), ft_strlen(str));
		if (new == NULL)
			return (NULL);
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

// static char	*add_line_return(char *source, t_mini *mini, int *fd)
// {
// 	char	*limiter;
// 	size_t	size;
// 	size_t	i;

// 	(void)mini;
// 	i = 0;
// 	size = ft_strlen(source);
// 	limiter = (char *)malloc(sizeof(char) * size + 2);
// 	if (limiter == NULL)
// 	{
// 		write(2, "here_doc error\n", 15);
// 		close(*fd);
// 	}
// 	while (i < size)
// 	{
// 		limiter[i] = source[i];
// 		i++;
// 	}
// 	limiter[i] = '\n';
// 	limiter[i + 1] = '\0';
// 	return (limiter);
// }

void	setup_here_doc(t_command *current, t_mini *mini, int *j)
{
	char	*dest;
	int		tmp_fd;
	int		i;

	// char	*limiter;
	i = *j;
	tmp_fd = open("tmp_file", O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (tmp_fd == -1)
		write(2, "here_doc : open error\n", 21);
	// limiter = add_line_return(current->file[i], mini, current->pipe_fd);
	dest = get_str(current->file[i], mini, NULL);
	write(tmp_fd, dest, ft_strlen(dest));
	close(tmp_fd);
	tmp_fd = open("tmp_file", O_RDONLY);
	if (tmp_fd == -1)
		write(2, "here_doc : open error\n", 21);
	if (dup2(tmp_fd, STDIN_FILENO) == -1)
		write(2, "here_doc : dup2 error\n", 21);
	close(tmp_fd);
	unlink("tmp_file");
	free(dest);
	// free(limiter);
}
