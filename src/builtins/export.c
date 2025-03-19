/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:52:00 by ncontin           #+#    #+#             */
/*   Updated: 2025/03/18 19:24:09 by ncontin          ###   ########.fr       */
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

static char	**copy_env(char **envp)
{
	int		i;
	char	**sorted_env;

	i = 0;
	while (envp[i])
		i++;
	sorted_env = malloc(sizeof(char *) * (i + 1));
	if (!sorted_env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		sorted_env[i] = ft_strdup(envp[i]);
		i++;
	}
	sorted_env[i] = NULL;
	return (sorted_env);
}

static int	find_len(char *s1, char *s2)
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

void	sort_env(char **sorted_env)
{
	int		i;
	int		j;
	char	*substr1;
	char	*substr2;
	char	*temp;

	i = 0;
	while (sorted_env[i])
	{
		j = i;
		while (sorted_env[++j])
		{
			substr1 = ft_substr(sorted_env[i], 0, find_equal(sorted_env[i]));
			substr2 = ft_substr(sorted_env[j], 0, find_equal(sorted_env[j]));
			if (ft_strncmp(substr1, substr2, find_len(substr1, substr2)) > 0)
			{
				temp = sorted_env[i];
				sorted_env[i] = sorted_env[j];
				sorted_env[j] = temp;
			}
			free(substr1);
			free(substr2);
		}
		i++;
	}
}

void	ft_export(char **envp)
{
	char	**sorted_env;
	int		i;

	sorted_env = copy_env(envp);
	sort_env(sorted_env);
	i = 0;
	while (sorted_env[i])
	{
		printf("declare -x %s\n", sorted_env[i]);
		i++;
	}
	free_array(sorted_env);
}
