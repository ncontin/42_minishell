/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:30:06 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/07 19:28:17 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// 42 Library
# include "libft/libft.h"

// Standard C Library Functions
# include <stdio.h>  // printf, perror
# include <stdlib.h> // malloc, free, exit, getenv
# include <string.h> // strerror

// File & Directory Operations
# include <dirent.h>   // opendir, readdir, closedir
# include <limits.h>   // PATH_MAX, other constants
# include <sys/stat.h> // stat, lstat, fstat
# include <unistd.h>   // access, open, read, close, unlink, dup, dup2, pipe,
						// getcwd, chdir, isatty, ttyname, fork, execve

// Process & Signal Handling
# include <fcntl.h>
# include <signal.h> // signal, sigaction, kill, sigemptyset, sigaddset
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/wait.h> // wait, waitpid, wait3, wait4

// Readline (Interactive Input)
# include <readline/history.h>  // add_history, rl_clear_history
# include <readline/readline.h> // readline, rl_on_new_line, rl_replace_line,
								// rl_redisplay

// Terminal Control (Optional: Add if using termios/curses)
// # include <termios.h>  // tcsetattr, tcgetattr
// # include <curses.h>   // tgetent, tputs, etc. (requires -lncurses)
// # include <sys/ioctl.h> // ioctl
# include <errno.h>

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

typedef enum s_arg_type
{
	ARGUMENT,
	COMMAND,
	OPTION,
	FILENAME,
	HERE_DOC_LIMITER,
	REDIRECTION,
	PIPE_OPERATOR,
	ENV_VAR
}						t_arg_type;

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
	t_arg_type			arg_type;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

typedef struct s_command
{
	int					nb_operator;
	int					pipe_fd[2];
	t_quotes			*arg_quotes;
	char				**argv;
	char				**file;
	pid_t				pid;
	t_operator			*operator;
	t_quotes			limiter_quotes;
	struct s_command	*next;
	struct s_command	*prev;
}						t_command;

typedef struct s_mini
{
	int					error;
	char				*input;
	char				**args;
	long long int		exit_code;
	t_env				*lst_env;
	t_token				*tokens;
	t_command			*cmds;
}						t_mini;

// expander
void					expander(t_mini *mini);
// init
void					init_mini(t_mini *mini);
void					init_envp(t_mini *mini);
char					**get_envp_array(t_env *lst_env);
// builtins
int						is_builtin(char *str);
void					execute_builtin(t_mini *mini, char **argv);
void					ft_pwd(void);
void					ft_echo(char **cmd_args);
void					free_array(char **array);
int						ft_cd(t_mini *mini);
int						find_min_len(char *s1, char *s2);
void					print_export(t_env_node **sorted_envp_cp, char **args);
t_env_node				**copy_envp_list(t_env_node **envp_cp);
void					replace_env(t_env_node *env_to_replace, char *arg);
void					ft_env(t_mini *mini);
void					ft_export(t_mini *mini, char **cmd_args);
void					ft_unset(t_mini *mini, char **cmd_args);
void					print_env(t_env_node **env_stack);
t_env_node				*find_last(t_env_node **my_envp);
int						find_equal(char *str);
char					*get_key(char *str);
char					*get_value(char *str);
void					ft_exit(t_mini *mini, char **cmd_args);
void					free_all(t_mini *mini);
long long				ft_atoll(const char *nptr, int *overflow);

// signals
void					sig_handler(int nbr);

// free
void					free_stack(t_env_node **my_envp);
void					free_array(char **array);
void					free_path(t_env *lst_env);
void					free_input(t_mini *mini);
// assign_type_argument
void					assign_type_argument(t_token *tokens);
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
void					error_pid(t_command *current, t_mini *mini);
// even_quotes.c
t_bool					is_even_quotes(char **tokens);
// free.c
void					free_token(t_token *token);
void					msg_and_free(t_token *tokens);
void					free_commands(t_command *cmds);
// get_env_argument.c
void					get_env_argument(t_mini *mini);
// is_mutil_strings.c
int						is_multi_strings(char *args, int i, t_bool dquotes,
							t_bool squotes);
// is_valid_token.c
t_bool					is_valid_token(t_token *tokens);
// multi_str.c
void					multi_str(char *args, int nb_strings, t_token **head,
							int i);
// parsing.c
t_command				*parsing(t_mini *mini);
// wordlen.c
int						wordlen(char const *s, t_bool dquotes, t_bool squotes);
// path.c
void					get_path(char **envp, t_env *lst_env);
char					**get_unix_path(char **envp);
char					*copy_command(char *unix_path, char *commands);
// merge_args.c
t_bool					merge_args(t_token **tokens);
// split_pipes.c
t_command				*split_pipe(t_token *tokens, t_command *cmds,
							t_command *new, int i);
// split_pipes_init.c
t_command				*create_cmd_list(t_command **cmds, t_token *tokens);
// create_argv.c
t_bool					str_and_operator(t_command *new, t_token *tokens);
//create_operator.c
void					create_operator(t_command *new, t_token *tokens);
// close_fd.c
void					close_fd(int *pipe_fd);
// executor.c
void					executor(t_mini *mini);
// handle_redirection.c
void					handle_redirection(t_command *current, t_mini *mini);
// execute_commands.c
int						execute_builtin_parent(t_mini *mini, t_command *cmd);
void					execute_cmd(t_command *current, char **envp,
							t_mini *mini);
// dup_create_pipe.c
void					duplicate_pipes(t_command *current, int *prev_fd,
							t_mini *mini);
void					create_pipe(t_command *current, t_mini *mini);
//here_doc.c
void					setup_here_doc(t_command *current, t_mini *data, int *j);
#endif
