/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:09:23 by aroullea          #+#    #+#             */
/*   Updated: 2025/03/19 16:07:01 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*prompt_join(char *s1, char *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*str;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	str = malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (str == NULL)
	{
		free(s1);
		error_msg("Memory allocation failed for prompt_join\n", 12);
	}
	ft_strlcpy(str, s1, len_s1 + 1);
	ft_strlcat(str, s2, (len_s1 + len_s2 + 2));
	free(s1);
	return (str);
}

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
	char	*line;

	while (*squotes == TRUE || *dquotes == TRUE)
	{
		line = readline("> ");
		if (line == NULL)
			error_msg("Memory allocation failed for prompt2\n", 12);
		is_odd_quotes(line, squotes, dquotes);
		if (*squotes == TRUE || *dquotes == TRUE)
			line = prompt_join(line, "\n");
		input = prompt_join(input, line);
		free(line);
		line = NULL;
	}
	return (input);
}

char	*user_input(char *str)
{
	char	*input;
	t_bool	squotes;
	t_bool	dquotes;

	squotes = FALSE;
	dquotes = FALSE;
	input = readline(str);
	if (input == NULL)
		error_msg("Memory allocation failed for prompt1\n", 12);
	is_odd_quotes(input, &squotes, &dquotes);
	if (squotes == TRUE || dquotes == TRUE)
	{
		input = prompt_join(input, "\n");
		input = read_new_input(input, &squotes, &dquotes);
	}
	return (input);
}
