/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:52:47 by aroullea          #+#    #+#             */
/*   Updated: 2025/03/31 18:37:17 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	check_access(char *file)
{
	if (!(access(file, X_OK)))
	{
		write(2, file, ft_strlen(file));
		write(2, " :No such file or directory")
		return (FALSE);
	}
	return (TRUE);
}
void	executor(t_command *cmds)
{
	t_command	*current;

	current = cmds;
	if (current->file != NULL)
		if (check_access(current->file) == FALSE)
			current = current->next;
}
