/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:01:48 by ncontin           #+#    #+#             */
/*   Updated: 2025/03/21 14:17:37 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// void	ft_unset(t_env_node **envp_cp, char *input)
// {
// 	char		*substr;
// 	char		*temp;
// 	t_env_node	*current;

// 	while (current)
// 	{
// 		substr = ft_substr(current->env_string, 0,
// 				find_equal(current->env_string));
// 		if (ft_strncmp(input, substr, ft_strlen(input)) == 0)
// 		{
// 			while (current && current->next)
// 			{
// 				temp = current;
// 				current = current->next;
// 				current->next = temp;
// 				current = current->next;
// 			}
// 			current = NULL;
// 		}
// 		free(substr);
// 		current = current->next;
// 	}
// }

void	ft_unset(t_env_node **envp_cp, char *input)
{
	t_env_node	*current;
	t_env_node	*prev;

	current = *envp_cp;
	prev = NULL;
	while (current)
	{
		if (ft_strncmp(input, current->key, ft_strlen(current->key)) == 0)
		{
			if (prev == NULL)
				*envp_cp = current->next;
			else
				prev->next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}
