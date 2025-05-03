/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:47:09 by ncontin           #+#    #+#             */
/*   Updated: 2025/05/03 12:15:10 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	display_export(t_env *current)
{
	size_t	len;

	while (current != NULL)
	{
		len = ft_strlen(current->key) + 1;
		if (ft_strncmp(current->key, "_", len) != 0)
		{
			if (current->key)
				printf("declare -x %s", current->key);
			if (current->value)
				printf("=\"%s\"", current->value);
			printf("\n");
		}
		current = current->next;
	}
}

void	print_export(t_env *sorted_envp_cp)
{
	if (sorted_envp_cp == NULL)
		return ;
	display_export(sorted_envp_cp);
}
