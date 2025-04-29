/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:47:09 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/29 07:50:34 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	display_export(t_env_node *current)
{
	size_t	len;

	while (current)
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

void	print_export(t_env_node **sorted_envp_cp, char **args)
{
	t_env_node	*current;

	if (!(*sorted_envp_cp) && !sorted_envp_cp)
		return ;
	if (args[0] && !args[1])
	{
		if (sorted_envp_cp && *sorted_envp_cp)
		{
			current = *sorted_envp_cp;
			display_export(current);
		}
	}
}
