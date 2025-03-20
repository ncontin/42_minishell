/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:01:48 by ncontin           #+#    #+#             */
/*   Updated: 2025/03/20 18:40:56 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}
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
	char		*substr;
	t_env_node	*current;
	t_env_node	*prev;

	current = *envp_cp;
	prev = NULL;
	while (current)
	{
		substr = ft_substr(current->env_string, 0,
				find_equal(current->env_string));
		if (ft_strncmp(input, substr, ft_strlen(input)) == 0)
		{
			if (prev == NULL)
				*envp_cp = current->next;
			else
				prev->next = current->next;
			free(current->env_string);
			free(current);
			free(substr);
			return ;
		}
		free(substr);
		prev = current;
		current = current->next;
	}
}
