/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:52:47 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/28 17:43:25 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(t_command *current, int *prev_fd, t_mini *mini)
{
	char	**envp;

	envp = NULL;
	child_signal();
	update_underscore(current, mini->lst_env->envp_cp);
	if (current->next != NULL && current->next->check_here_doc == FALSE)
	{
		close(current->pipe_fd[0]);
		current->pipe_fd[0] = -1;
	}
	close_child_heredoc_fd(mini->cmds, current);
	duplicate_pipes(current, prev_fd, mini);
	if (current->operator != NONE)
		handle_redirection(current, mini);
	if (get_envp_array(mini->lst_env, &envp) == 1)
	{
		write(STDERR_FILENO, "child envp :", 12);
		write(STDERR_FILENO, "memory allocation failed\n", 26);
		if (*prev_fd != -1)
			close(*prev_fd);
		free_exit(mini);
		exit(EXIT_FAILURE);
	}
	execute_cmd(current, envp, mini);
}

static int	find_last_argument(char **args)
{
	int	i;

	i = 0;
	while (args[i] != NULL)
		i++;
	i--;
	return (i);
}

void	update_underscore(t_command *cmd, t_env_node **envp_cp)
{
	t_env_node	*current;
	char		*tmp;
	int			i;

	if (cmd->argv[0][0] == '\0')
		return ;
	current = *envp_cp;
	i = find_last_argument(cmd->argv);
	while (current != NULL)
	{
		if (strncmp(current->key, "_", ft_strlen(current->key) + 1) == 0)
		{
			tmp = ft_strdup(cmd->argv[i]);
			if (tmp == NULL)
			{
				free(current->value);
				current->value = NULL;
				return ;
			}
			free(current->value);
			current->value = tmp;
			return ;
		}
		current = current->next;
	}
}

void	parent_process(int *prev_fd, t_command *current)
{
	if (*prev_fd != -1)
	{
		close(*prev_fd);
		*prev_fd = -1;
	}
	if (current->next != NULL && current->next->check_here_doc == FALSE)
	{
		close(current->pipe_fd[1]);
		current->pipe_fd[1] = -1;
		*prev_fd = current->pipe_fd[0];
	}
	close_parent_heredoc_fd(current);
}
