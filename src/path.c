/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:57:25 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/12 12:30:23 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_path(char **envp, t_env *lst_env)
{
	char	**mypath;
	char	*env_path;

	mypath = NULL;
	lst_env->envp = envp;
	env_path = getenv("PATH");
	if (env_path != NULL)
	{
		mypath = ft_split(env_path, ':');
		if (mypath == NULL)
			error_msg("Path : memory allocation failed\n", 12);
	}
	lst_env->path = mypath;
}

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
	if (mypath == NULL)
		write(2, "no PATH found \n", 15);
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
