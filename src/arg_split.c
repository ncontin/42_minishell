/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:32:53 by aroullea          #+#    #+#             */
/*   Updated: 2025/03/17 10:53:30 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_args(char const *s, int count, int i, t_bool in_word)
{
	t_bool	in_quotes;
	char	quote_char;

	in_quotes = FALSE;
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			if (in_quotes == FALSE)
			{
				if (in_word == FALSE) // for this argument -->inf"ile".txt
					count++;
				in_quotes = TRUE;
				in_word = TRUE;
				quote_char = s[i];
			}
			else
			{
				if (s[i + 1] == quote_char) // for this argument -->"arg1""arg2"
					i++;
				else
				{
					if (is_operator(s + (i + 1), 0, &i))
						in_word = FALSE;
					in_quotes = FALSE;
					quote_char = 0;
				}
			}
		}
		else if ((!in_quotes) && is_operator(s + i, 0, &i))
		{
			if (in_word)
			{
				in_word = FALSE;
				if (s[i] != ' ')
					count++;
			}
			else if (is_operator(s + i, 1, &i))
				count++;
		}
		else if (!in_word && !in_quotes)
		{
			in_word = TRUE;
			count++;
		}
		i++;
	}
	return (count);
}

static int	wordlen(char const *s, t_bool dquotes, t_bool squotes)
{
	int		len;
	int		next;

	len = 0;
	while (s[len])
	{
		if ((s[len] == '"' && dquotes) || (s[len] == '\'' && squotes))
		{
			next = len + 1;
			if ((s[next] == '"' && dquotes) || (s[next] == '\'' && squotes))
				len += 2;
			else
			{
				if (s[len] == '"')
					dquotes = FALSE;
				else if (s[len] == '\'')
					squotes = FALSE;
				len++;
			}
		}
		else if ((s[len] == '"' && !squotes) || (s[len] == '\'' && !dquotes))
		{
			if (s[len] == '"')
				dquotes = TRUE;
			else if (s[len] == '\'')
				squotes = TRUE;
			len++;
			while (s[len] == '"' || s[len] == '\'')
			{
				if (s[len] == '"')
					dquotes = !dquotes;
				else if (s[len] == '\'')
					squotes = !squotes;
				len++;
			}
		}
		else if (!dquotes && !squotes && is_operator(s + len, 0, &len))
		{
			if (len == 0 || len == 1)
				len++;
			else if (s[len - 1] == '>' || s[len - 1] == '<')
				len--;
			break ;
		}
		else
			len++;
	}
	return (len);
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
		while (*s == ' ')
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
	int		nb_args;
	char	**str;

	if (!s)
		return (NULL);
	nb_args = count_args(s, 0, 0, FALSE);
	str = (char **) malloc(sizeof(char *) * (nb_args + 1));
	if (str == NULL)
		return (NULL);
	str = sort(s, str, nb_args);
	return (str);
}
