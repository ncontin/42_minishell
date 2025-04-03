/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:04:41 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/03 12:50:52 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_node	*find_last(t_env_node **my_envp)
{
	t_env_node *last;

	last = *my_envp;
	while (last->next)
		last = last->next;
	return (last);
}
