/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:52:00 by ncontin           #+#    #+#             */
/*   Updated: 2025/03/18 18:08:19 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	ft_export(char **envp)
{
	int		i;
	char	**sorted_env;
	char	*min;
	int		j;

	// sorted = malloc(sizeof(envp));
	sorted_env = envp;
	i = 0;
	while (sorted_env[i] && sorted_env[i + 1])
	{
		printf("declare -x %s\n", sorted_env[i]);
		printf("diff %d\n", ft_strcmp(envp[i + 1], envp[i]));
		// printf("strchr: %s\n", ft_substr(envp[i], 0, )
		j = i;
		while (sorted_env[j] && sorted_env[j + 1])
		{
			if (ft_strcmp(envp[j + 1], envp[j]) < 0)
			{
				min = envp[j];
				//		printf("min: %s\n", min);
			}
			j++;
		}
		i++;
	}
	printf("min: %s\n", min);
	// export
}
