/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 18:31:31 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/07 18:48:30 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin_parent(t_mini *mini, t_command *cmd)
{
	int	exec;

	exec = 0;
	if (is_builtin(cmd->argv[0]))
	{
		execute_builtin(mini, cmd->argv);
		exec = 1;
	}
	return (exec);
}

void	execute_cmd(t_command *current, char **envp, t_mini *mini)
{
	char	**unix_path;
	char	*path;
	int		i;

	i = 0;
	if (current->argv == NULL)
	{
		free_all(mini);
		free_array(envp);
		exit (EXIT_SUCCESS);
	}
	if (is_builtin(current->argv[0]))
	{
		execute_builtin(mini, current->argv);
		free_all(mini);
		free_array(envp);
		exit(EXIT_SUCCESS);
	}
	if (access(current->argv[0], X_OK) == 0)
	{
		if (execve(current->argv[0], current->argv, envp) == -1)
		{
			free_commands(mini->cmds);
			exit(errno);
		}
	}
	else
	{
		unix_path = get_unix_path(mini->lst_env->envp);
		while (unix_path[i])
		{
			path = copy_command(unix_path[i], current->argv[0]);
			if (access(path, X_OK) == 0)
			{
				if (execve(path, current->argv, envp) == -1)
				{
					free_commands(mini->cmds);
					exit(errno);
				}
			}
			free(path);
			i++;
		}
		write(2, current->argv[0], ft_strlen(current->argv[0]));
		write(2, ": command not found\n", 20);
		free_array(unix_path);
		free_all(mini);
		free_array(envp);
		exit(errno);
	}
}
