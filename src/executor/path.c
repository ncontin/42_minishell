/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:57:25 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/24 11:53:21 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_unix_path(char **envp)
{
	char	**mypath;
	char	*env_path;

	mypath = NULL;
	while (envp && *envp)
	{
		if (!ft_strncmp("PATH", *envp, 4))
		{
			env_path = *envp + 5;
			if (env_path[0] == '\0')
				break ;
			mypath = ft_split(env_path, ':');
			if (mypath == NULL)
			{
				write(2, "memory allocation failed in unix path", 37);
				return (NULL);
			}
			break ;
		}
		envp++;
	}
	return (mypath);
}

char	*copy_command(char *unix_path, char *commands)
{
	char	*path;
	size_t	len_path;
	size_t	len_cmd;

	len_path = ft_strlen(unix_path);
	len_cmd = ft_strlen(commands);
	path = (char *)malloc(len_path + len_cmd + 2);
	if (path == NULL)
	{
		write(2, "memory allocation failed in get path", 36);
		return (NULL);
	}
	ft_strlcpy(path, unix_path, len_path + 1);
	ft_strlcat(path, "/", len_path + 2);
	ft_strlcat(path, commands, (len_path + len_cmd + 2));
	return (path);
}
