/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:19:29 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/18 14:37:02 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_command(t_arg_type arg_type)
{
	if (arg_type == COMMAND)
		return (TRUE);
	if (arg_type == OPTION)
		return (TRUE);
	if (arg_type == ARGUMENT)
		return (TRUE);
	return (FALSE);
}

t_bool	is_recognized_operator(t_operator operator)
{
	if (operator == OUTPUT)
		return (TRUE);
	if (operator == INPUT)
		return (TRUE);
	if (operator == APPEND)
		return (TRUE);
	if (operator == HEREDOC)
		return (TRUE);
	return (FALSE);
}

t_bool	is_filename_or_limiter(t_arg_type arg_type)
{
	if (arg_type == FILENAME)
		return (TRUE);
	if (arg_type == HERE_DOC_LIMITER)
		return (TRUE);
	return (FALSE);
}
