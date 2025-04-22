/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:08:41 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/22 12:02:54 by aroullea         ###   ########.fr       */
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
		{
			free(lst_env);
			error_msg("Path : memory allocation failed", 12);
		}
	}
	lst_env->path = mypath;
}

void	init_mini(t_mini *mini)
{
	mini->args = NULL;
	mini->exit_code = 0;
	mini->lst_env = malloc(sizeof(t_env));
	if (!mini->lst_env)
	{
		write(STDERR_FILENO, "Memory allocation failed in init_mini\n", 38);
		exit(EXIT_FAILURE);
	}
	mini->tokens = NULL;
	mini->cmds = NULL;
	mini->error = 0;
}
