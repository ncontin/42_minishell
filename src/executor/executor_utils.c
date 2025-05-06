/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 08:20:10 by aroullea          #+#    #+#             */
/*   Updated: 2025/05/06 08:40:13 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_open(char *filename, int flags, mode_t mode)
{
	int	fd;

	fd = open(filename, flags, mode);
	if (fd != -1)
		close(fd);
}

void	precreate_files(t_command *cmd)
{
	t_command	*current;
	int			i;
	int			flags;

	i = 0;
	current = cmd;
	while (current != NULL)
	{
		while (i < current->nb_operator)
		{
			if (current->operator[i] == OUTPUT)
			{
				flags = O_WRONLY | O_TRUNC | O_CREAT;
				handle_open(current->file[i], flags, 0664);
			}
			else if (current->operator[i] == APPEND)
			{
				flags = O_WRONLY | O_APPEND | O_CREAT;
				handle_open(current->file[i], flags, 0664);
			}
			i++;
		}
		i = 0;
		current = current->next;
	}
}
