/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:03:23 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/14 12:30:13 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_env_node **env_stack)
{
	t_env_node	*current;

	if (!(*env_stack) && !env_stack)
		return ;
	current = *env_stack;
	while (current)
	{
		if (current->key)
			printf("%s", current->key);
		if (current->value)
			printf("=%s", current->value);
		printf("\n");
		current = current->next;
	}
}

int	find_equal(char *str)
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

char	*get_key(char *str)
{
	char	*key;
	int		equal_index;

	equal_index = find_equal(str);
	if (str[equal_index - 1] && str[equal_index - 1] == '+')
		equal_index -= 1;
	key = ft_substr(str, 0, equal_index);
	return (key);
}

char	*get_value(char *str)
{
	char	*value;
	int		equal_index;

	equal_index = find_equal(str);
	value = ft_substr(str, equal_index + 1, ft_strlen(str) - (equal_index + 1));
	return (value);
}

int	find_min_len(char *s1, char *s2)
{
	int	s1_len;
	int	s2_len;
	int	len;

	s2_len = ft_strlen(s2);
	s1_len = ft_strlen(s1);
	if (s1_len < s2_len)
		len = s1_len;
	else
		len = s2_len;
	return (len);
}
