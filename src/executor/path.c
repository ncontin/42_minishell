/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:57:25 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/22 11:04:59 by aroullea         ###   ########.fr       */
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

int	*is_user_in_bin(t_mini *mini, t_command *cmd, char **envp)
{
	char	*path;
	char	*bin_folder;

	while (envp && *envp)
	{
		if ((ft_strncmp(*envp, "PWD", 3)) == 0)
		{
			bin_folder = *envp + 4;
			if (ft_strncmp(bin_folder, "/usr/bin", 8) == 0)
			{
				path = copy_command(bin_folder, cmd->argv[0]);
				if (execve(path, cmd->argv, envp) == -1)
				{
					write(STDERR_FILENO, "execve error\n", 13);
					free(path);
					clean_exit(mini, envp, 1);
				}
			}
		}
		envp++;
	}
	return (0);
}
