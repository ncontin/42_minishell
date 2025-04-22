/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:04:55 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/22 17:26:57 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_tilde(char **source, int i, t_mini *mini)
{
	t_env_node	*current;
	char		*str;
	char		*arg;

	arg = *source;
	current = *mini->lst_env->envp_cp;
	if ((arg[i] == '~') && (arg[i + 1] == '\0'))
	{
		while (current != NULL)
		{
			if (strncmp(current->key, "HOME", ft_strlen(current->key) + 1) == 0)
			{
				str = ft_strdup(current->value);
				if (str == NULL)
				{
					free_exit(mini);
					exit (EXIT_FAILURE);
				}
				free(arg);
				*source = str;
				break ;
			}
			current = current->next;
		}
	}
}
