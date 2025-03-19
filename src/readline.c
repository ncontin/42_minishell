/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:27:15 by aroullea          #+#    #+#             */
/*   Updated: 2025/03/19 12:02:09 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	is_odd_quotes(char *input, t_bool *squotes, t_bool *dquotes)
{
	int		i;

	i = 0;
	if (input == NULL)
		return ;
	while (input[i] != '\0')
	{
		if (input[i] == '\'')
			*squotes = !(*squotes);
		if (input[i] == '"')
			*dquotes = !(*dquotes);
		i++;
	}
}

static char	*read_new_input(char *input, t_bool *squotes, t_bool *dquotes)
{
	char	*arg;
	char	*line;

	line = NULL;
	arg = readline("> ");
	is_odd_quotes(arg, squotes, dquotes);
	if (*squotes == TRUE || *dquotes == TRUE)
		line = shell_join(arg, "\n", ft_strlen(arg), 1);
	arg = shell_join(input, line, ft_strlen(input), ft_strlen(line));
	free(line);
	line = NULL;
	while (*squotes == TRUE || *dquotes == TRUE)
	{
		line = readline("> ");
		is_odd_quotes(line, squotes, dquotes);
		if (*squotes == TRUE || *dquotes == TRUE)
			line = shell_join(line, "\n", ft_strlen(line), 1);
		arg = shell_join(arg, line, ft_strlen(arg), ft_strlen(line));
		free(line);
		line = NULL;
	}
	return (arg);
}

static char	*user_input(void)
{
	char	*input;
	char	*new_line;
	t_bool	squotes;
	t_bool	dquotes;

	new_line = NULL;
	squotes = FALSE;
	dquotes = FALSE;
	input = readline("minishell> ");
	is_odd_quotes(input, &squotes, &dquotes);
	if (squotes == TRUE || dquotes == TRUE)
	{
		input = shell_join(input, "\n", ft_strlen(input), 1);
		input = read_new_input(input, &squotes, &dquotes);
	}
	return (input);
}

void	line_read(t_env *lst_env)
{
	char	*input;

	while (1)
	{
		input = user_input();
		if (input && (ft_strlen(input) > 0))
		{
			if (ft_strncmp("exit", input, ft_strlen(input)) == 0)
			{
				free(input);
				break ;
			}
			parsing(lst_env, input);
			add_history(input);
			free(input);
		}
	}
	rl_clear_history();
}
