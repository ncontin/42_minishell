/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:45:52 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/28 18:48:31 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_str_error(t_mini *mini, int here_doc_fd, char *new, char *limiter)
{
	close(here_doc_fd);
	if (new != NULL)
		free(new);
	free(limiter);
	free_exit(mini);
	exit (130);
}

void	here_doc_error(char *str_error, int here_doc_pipe[2])
{
	if (here_doc_pipe != NULL)
	{
		if (here_doc_pipe[0] != -1)
			close(here_doc_pipe[0]);
		if (here_doc_pipe[1] != -1)
			close(here_doc_pipe[1]);
	}
	write(STDERR_FILENO, "here_doc :", 10);
	write(STDERR_FILENO, str_error, ft_strlen(str_error));
	write(STDERR_FILENO, "\n", 1);
}

void	here_doc_exit(t_mini *mini, char *limiter, char *str, int *hd_pipe)
{
	free(limiter);
	free(str);
	free_exit(mini);
	if (hd_pipe != NULL)
		close(hd_pipe[1]);
}

void	expand_error(t_mini *mini, char *limiter, char *str)
{
	write(STDERR_FILENO, "Memory allocation failed in expander\n", 37);
	if (str != NULL)
		free(str);
	free(limiter);
	free(mini->hd_input);
	free_exit(mini);
	exit(2);
}
