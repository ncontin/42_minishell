/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:29:57 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/02 19:29:58 by ncontin          ###   ########.fr       */
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
