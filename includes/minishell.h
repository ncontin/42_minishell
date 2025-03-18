/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:30:06 by aroullea          #+#    #+#             */
/*   Updated: 2025/03/17 15:13:07 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum s_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef struct s_env
{
	char	**envp;
	char	**path;
}	t_env;

typedef struct s_parser
{
	char const	*s;
	t_bool		in_word;
	t_bool		in_quotes;
	int			count;
	char		quote_char;
}	t_parser;

//path.c
void	get_path(char **envp, t_env *lst_env);
//readline.c
void	line_read(t_env *lst_env);
//error.c
void	error_msg(char *message, int error);
//free.c
void	free_struct(t_env *lst_env);
//parsing.c
void	parsing(t_env *lst_env, char *input);
//arg_split.c
char	**arg_split(char const *s);
//arg_split_utils.c
t_bool	is_operator(char const *c, int no_space, int *len);
//count_args
int		count_args(t_parser *parser);
//wordlen.c
int		wordlen(char const *s, t_bool dquotes, t_bool squotes);
#endif
