/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:00:44 by aroullea          #+#    #+#             */
/*   Updated: 2025/05/01 06:34:44 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_or_create_pwd(t_env_node *current, t_mini *mini, char *key_name,
		char *pwd)
{
	size_t	len;

	while (current)
	{
		len = ft_strlen(current->key) + 1;
		if (ft_strncmp(current->key, key_name, len) == 0)
		{
			free(current->value);
			current->value = pwd;
			return (0);
		}
		if (current->next == NULL)
		{
			if (add_export_env(mini->lst_env, key_name, mini) == 1)
				return (1);
		}
		current = current->next;
	}
	return (0);
}
