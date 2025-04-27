/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:32:53 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/27 09:48:53 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_parser	init_parser(char const *str)
{
	t_parser	parser;

	parser.s = str;
	parser.in_word = FALSE;
	parser.in_quotes = FALSE;
	parser.count = 0;
	parser.quote_char = 0;
	return (parser);
}

static void	copyword(char *dest, char const *s, int len, int i)
{
	int		j;

	j = 0;
	while (i < len)
		dest[j++] = s[i++];
	dest[j] = '\0';
}

static char	**sort(char const *s, char **str, int nb_args)
{
	int	len;
	int	k;

	k = 0;
	while (k < nb_args)
	{
		while (ft_isspace(*s) == 1)
			s++;
		len = wordlen(s, FALSE, FALSE);
		str[k] = (char *) malloc(sizeof(char) * (len + 1));
		if (str[k] == NULL)
		{
			while (k >= 0)
				free (str[k--]);
			free (str);
			return (NULL);
		}
		copyword(str[k], s, len, 0);
		k++;
		s += len;
	}
	str[nb_args] = NULL;
	return (str);
}

char	**arg_split(char const *s)
{
	int			nb_args;
	char		**str;
	t_parser	parser;

	if (!s)
		return (NULL);
	parser = init_parser(s);
	nb_args = count_args(&parser, 0);
	str = (char **) malloc(sizeof(char *) * (nb_args + 1));
	if (str == NULL)
		return (NULL);
	str = sort(s, str, nb_args);
	return (str);
}
