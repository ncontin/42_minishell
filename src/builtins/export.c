/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:52:00 by ncontin           #+#    #+#             */
/*   Updated: 2025/03/21 12:53:51 by ncontin          ###   ########.fr       */
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

// chained list
// static void	add_export(char **args, t_export_node **env_stack)
// {
// 	t_export_node	*env;
// 	t_export_node	*last;
// 	int				i;

// 	i = 1;
// 	while (args[i])
// 	{
// 		env = malloc(sizeof(t_export_node));
// 		if (!env)
// 			return ;
// 		env->string = ft_strdup(args[i]);
// 		env->next = NULL;
// 		if (!(*env_stack))
// 		{
// 			*env_stack = env;
// 		}
// 		else
// 		{
// 			last = *env_stack;
// 			while (last->next)
// 			{
// 				last = last->next;
// 			}
// 			last->next = env;
// 		}
// 		i++;
// 	}
// }

// static char	**add_env(char **args)
// {
// 	char	**env_added;
// 	int		i;
// 	int		args_len;

// 	args_len = 0;
// 	while (args[args_len])
// 		args_len++;
// 	env_added = malloc((args_len + 1) * sizeof(char *));
// 	if (!env_added)
// 		return (NULL);
// 	i = 0;
// 	while (args[i + 1])
// 	{
// 		env_added[i] = ft_strdup(args[i + 1]);
// 		printf("added\n");
// 		i++;
// 	}
// 	env_added[i] = NULL;
// 	return (env_added);
// }

// static void	print_export(char **sorted_env, char **args,
// 		t_export_node **env_stack)
// {
// 	int		i;
// 	char	*substr;

// 	i = 0;
// 	if (args[0] && !args[1])
// 	{
// 		while (sorted_env[i])
// 		{
// 			substr = ft_substr(sorted_env[i], 0, find_equal(sorted_env[i]));
// 			printf("declare -x %s=\"%s\"\n", substr, (ft_strchr(sorted_env[i],
// 						'=') + 1));
// 			free(substr);
// 			i++;
// 		}
// 		print_env_stack(env_stack);
// 	}
// }

// void	ft_export_node(char **args, char **envp)
// {
// 	char			**sorted_env;
// 	t_export_node	*env_stack;

// 	env_stack = NULL;
// 	sorted_env = copy_env(envp);
// 	sort_env(sorted_env);
// 	add_export(args, &env_stack);
// 	print_export(sorted_env, args, &env_stack);
// 	free_array(sorted_env);
// }

t_env_node	**copy_envp_list(t_env_node **envp_cp)
{
	t_env_node	**ft_envp;
	t_env_node	*node;
	t_env_node	*last;
	t_env_node	*current;

	current = *envp_cp;
	ft_envp = malloc(sizeof(t_env_node *));
	if (!ft_envp)
		return (NULL);
	*ft_envp = NULL;
	while (current)
	{
		node = malloc(sizeof(t_env_node));
		if (!node)
			return (NULL);
		node->env_string = ft_strdup(current->env_string);
		node->next = NULL;
		if (!(*ft_envp))
			*ft_envp = node;
		else
		{
			last = find_last(ft_envp);
			last->next = node;
		}
		current = current->next;
	}
	return (ft_envp);
}

t_env_node	*find_min(t_env_node **envp_cp)
{
	t_env_node	*current;
	t_env_node	*min;
	char		*substr1;
	char		*substr2;

	if (!*envp_cp)
		return (NULL);
	min = *envp_cp;
	current = (*envp_cp)->next;
	while (current)
	{
		substr1 = ft_substr(min->env_string, 0, find_equal(min->env_string));
		substr2 = ft_substr(current->env_string, 0,
				find_equal(current->env_string));
		if (ft_strncmp(substr1, substr2, find_len(substr1, substr2)) > 0)
			min = current;
		free(substr1);
		free(substr2);
		current = current->next;
	}
	return (min);
}

static void	sort_env(t_env_node **envp_cp)
{
	t_env_node	*current;
	t_env_node	*temp;
	char		*substr1;
	char		*substr2;
	char		*temp_str;

	if (!envp_cp || !*envp_cp)
		return ;
	current = *envp_cp;
	while (current)
	{
		temp = current->next;
		while (temp)
		{
			substr1 = ft_substr(current->env_string, 0,
					find_equal(current->env_string));
			substr2 = ft_substr(temp->env_string, 0,
					find_equal(temp->env_string));
			if (ft_strncmp(substr1, substr2, find_len(substr1, substr2)) > 0)
			{
				temp_str = current->env_string;
				current->env_string = temp->env_string;
				temp->env_string = temp_str;
			}
			free(substr1);
			free(substr2);
			temp = temp->next;
		}
		current = current->next;
	}
}
void	ft_export(t_env *lst_env, char **args)
{
	t_export_node	*env_stack;
	char			**sorted_env;

	(void)args;
	env_stack = NULL;
	sorted_env = NULL;
	// You might need to implement a function to convert env_node to char**
	lst_env->sorted_envp_cp = copy_envp_list(lst_env->envp_cp);
	sort_env(lst_env->sorted_envp_cp);
	// add_export(args, &env_stack);
	print_env_stack(lst_env->sorted_envp_cp);
	// print_export(sorted_env, args, &env_stack);
	free_stack(lst_env->sorted_envp_cp);
	// 	if (sorted_env)
	// 		free_array(sorted_env);
}
