/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:30:06 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/01 14:48:54 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>

typedef enum s_bool
{
	FALSE,
	TRUE
}						t_bool;

typedef enum s_quotes
{
	NO_QUOTES,
	SINGLE,
	DOUBLE
}						t_quotes;

typedef enum s_operator
{
	NONE,
	OUTPUT,
	INPUT,
	PIPE,
	APPEND,
	HEREDOC
}						t_operator;

typedef struct s_env_node
{
	char				*key;
	char				*value;
	struct s_env_node	*next;
}						t_env_node;

typedef struct s_env
{
	char				**envp;
	char				**path;
	t_env_node			**envp_cp;
	t_env_node			**sorted_envp_cp;
}						t_env;

typedef struct s_parser
{
	char const			*s;
	int					count;
	char				quote_char;
	t_bool				in_word;
	t_bool				in_quotes;
}						t_parser;

typedef struct s_token
{
	char				*argument;
	t_quotes			quotes;
	t_bool				linked;
	t_operator			operator;
	struct s_token		*next;
}						t_token;

typedef struct s_mini
{
	char				*input;
	char				**args;
	long long int		exit_code;
	t_env				*lst_env;
	t_token				*tokens;
}						t_mini;

// builtins
int						is_builtin(char *str);
void					execute_builtin(t_mini *mini);
void					ft_pwd(void);
void					ft_echo(t_mini *mini);
void					free_array(char **array);
int						ft_cd(t_mini *mini);
int						find_min_len(char *s1, char *s2);
void					print_export(t_env_node **sorted_envp_cp, char **args);
t_env_node				**copy_envp_list(t_env_node **envp_cp);
void					replace_env(t_env_node *env_to_replace, char *arg);
void					ft_env(t_mini *mini);
void					ft_export(t_mini *mini);
void					ft_unset(t_mini *mini);
void					init_envp(t_env *lst_env);
void					print_env_stack(t_env_node **env_stack);
t_env_node				*find_last(t_env_node **my_envp);
int						find_equal(char *str);
char					*get_key(char *str);
char					*get_value(char *str);
void					ft_exit(t_mini *mini);
void					free_all(t_mini *mini);
long long				ft_atoll(const char *nptr, int *overflow);

// free
void					free_stack(t_env_node **my_envp);
void					free_array(char **array);
void					free_path(t_env *lst_env);
void					free_input(t_mini *mini);

void					line_read(t_mini *mini);
// arg_split.c
char					**arg_split(char const *s);
// arg_split_utils.c
t_bool					is_operator(char const *c, int no_space, int *len);
// check_quotes.c
void					check_quotes(char *args, t_token *current);
int						get_size(char *args);
char					*rm_quotes(char *args, int size);
// count_args.c
int						count_args(t_parser *parser);
// create_list.c
t_token					*create_list(char **tokens);
// create_list_init.c
t_token					*init_new_list(t_token *head);
void					lst_add_new(t_token **head, t_token *new);
// check_operator.c
void					assign_operator(t_token *tokens);
// error.c
void					error_msg(char *message, int error);
// even_quotes.c
t_bool					is_even_quotes(char **tokens);
// free.c
void					free_struct(t_env *lst_env);
void					free_array(char **array);
void					free_token(t_token *token);
void					msg_and_free(t_token *tokens);
// is_mutil_strings.c
int						is_multi_strings(char *args, int i, t_bool dquotes,
							t_bool squotes);
// is_valid_token.c
t_bool					is_valid_token(t_token *tokens);
// multi_str.c
void					multi_str(char *args, int nb_strings, t_token **head,
							int i);
// parsing.c
void					parsing(t_mini *mini);
// arg_split.c
char					**arg_split(char const *s);
// arg_split_utils.c
t_bool					is_operator(char const *c, int no_space, int *len);
// count_args
int						count_args(t_parser *parser);
// wordlen.c
int						wordlen(char const *s, t_bool dquotes, t_bool squotes);
void					get_path(char **envp, t_env *lst_env);

#endif
