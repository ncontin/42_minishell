/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:30:06 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/28 12:11:39 by ncontin          ###   ########.fr       */
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
# include <sys/stat.h>
# include <sys/types.h>

extern int				g_signal_received;

typedef enum e_bool
{
	FALSE,
	TRUE
}						t_bool;

typedef enum e_quotes
{
	NO_QUOTES,
	SINGLE,
	DOUBLE
}						t_quotes;

typedef enum e_operator
{
	NONE,
	OUTPUT,
	INPUT,
	APPEND,
	HEREDOC,
	PIPE
}						t_operator;

typedef enum e_arg_type
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
	int					here_doc_fd;
	t_quotes			*arg_quotes;
	char				**argv;
	char				**file;
	pid_t				pid;
	t_bool				check_here_doc;
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
	int					expanded;
	t_env				*lst_env;
	t_token				*tokens;
	t_command			*cmds;
}						t_mini;

/* === INIT === */
void					init_mini(t_mini *mini);
void					init_envp(t_mini *mini);

/* === BUILTINS === */
int						is_builtin(char *str);
void					execute_builtin(t_mini *mini, char **argv);
void					ft_pwd(t_mini *mini);
void					ft_echo(char **cmd_args, long long int *exit_code);
int						ft_cd(t_mini *mini, char *path);
void					update_old_pwd(t_env_node **env_stack, char *old_pwd);
int						check_cd_path(char *path);
char					*get_env_value(t_env_node **envp_cp, char *key);
void					update_pwd(t_env_node **env_stack);
int						find_min_len(char *s1, char *s2);
void					print_export(t_env_node **sorted_envp_cp, char **args);
t_env_node				**copy_envp_list(t_env_node **envp_cp);
void					replace_env(t_env_node *env_to_replace, char *arg);
void					ft_env(t_mini *mini, char **cmd_args);
void					ft_export(t_mini *mini, char **cmd_args);
void					ft_unset(t_mini *mini, char **cmd_args);
void					ft_unset(t_mini *mini, char **cmd_args);
void					print_env(t_env_node **env_stack);
t_env_node				*find_last(t_env_node **my_envp);
int						find_equal(char *str);
char					*get_key(char *str, int *err_code);
char					*get_value(char *str, int *err_code);
void					ft_exit(t_mini *mini, char **cmd_args);
long long				ft_atoll(const char *nptr, int *overflow);
char					*del_spaces(char *str);
int						check_digit(char *str);
int						is_double_dash(char **cmd_args);

/* === SIGNAL === */
void					executor_signal(void);
void					child_signal(void);
void					handle_signals(void);
/* === FREEING === */
void					free_stack(t_env_node **my_envp);
void					free_array(char **array);
void					free_path(t_env *lst_env);
void					free_input(t_mini *mini);
void					free_exit(t_mini *mini);
void					free_token(t_token *token);
void					free_token_argument(t_token *token);
void					free_commands(t_command *cmds);
void					clean_exit(t_mini *mini, char **envp, int exit_code);
void					close_fd(int *pipe_fd);
/* === ERROR === */
void					error_msg(char *message, int error);
void					error_arg_split(t_mini *mini);
void					error_merge_args(t_mini *mini);
void					error_create_list(t_token **tokens, t_token *current);
void					error_split_pipe(t_mini *mini);
void					error_pid_executor(t_mini *mini, t_command *current,
							int *prev_fd);
void					error_dup2_executor(t_mini *mini, int error_code,
							int *prev_fd);
void					error_open_executor(t_mini *mini, int error_code);
void					print_executor_error(char *msg, char *arg);
void					error_path(t_mini *mini, char **envp, int err_code,
							t_command *cmd);
void					print_file_error(char *filename, char *message);
void					get_str_error(t_mini *mini, int here_fd, char *new,
							char *limiter);
void					print_error_cd(char *msg, char *arg);
void					print_error_chdir(char *path, char *pwd, t_mini *mini);
void					here_doc_error(char *str_error, int here_doc_pipe[2]);
void					copy_env_error(t_env_node **ft_envp, t_mini *mini);
void					envp_to_list_error(t_mini *mini);
/* ====== READLINE ====== */
void					line_read(t_mini *mini);
/* ====== PARSING ====== */
t_command				*parsing(t_mini *mini);
/* === CHECK OPERATOR === */
void					assign_operator(t_token *tokens);
void					assign_type_argument(t_token *tokens);
t_bool					is_even_quotes(char **tokens);
t_bool					is_valid_operator(char **args);
t_bool					is_valid_token(t_token *tokens);
int						is_tilde(t_mini *mini);
void					is_dollar_alone(t_mini *mini);
/* === CREATE LIST === */
t_token					*create_list(char **tokens);
t_token					*init_new_list(t_token *head);
void					lst_add_new(t_token **head, t_token *new);
void					check_quotes(char *args, t_token *current);
int						get_size(char *args);
char					*rm_quotes(char *args, int size);
void					multi_str(char *args, int nb_strings, t_token **head,
							int i);
int						is_multi_strings(char *args, int i, t_bool dquote,
							t_bool squote);
/* === EXPANDER === */
int						expander(t_mini *mini, t_token *tokens,
							t_token *current);
char					*expand_exit_status(char *arg, t_mini *mini);
void					free_three(char *a, char *b, char *c);
char					*get_current_value(char *value);
char					*handle_strjoin(char *s1, char *s2);
char					*handle_substr(char *src, int start, size_t len);
char					*expand_shell_vars(char *arg, t_mini *mini,
							int *err_code);
char					*get_env_var(char *full_str, t_env_node *current, int i,
							int *err_code);
int						split_words(t_mini *mini, t_token **tokens);
int						find_word_len(char *arg, int len);
int						get_array_size(char **array);
int						has_space(char *str);
t_token					*create_token(char *arg);
int						add_new_token(t_token *token, char *word,
							t_token *next_og);
int						is_dollar(t_token **tokens);
int						is_nl_char(t_token **tokens);
// char					*expand_special_vars(char *arg, t_mini *mini,
						int *err_code);
void					replace_tokens(t_token **tokens);
void					advance_token(t_token **tokens, t_token **current);
int						handle_nl_expand(t_token **tokens);
/* === MERGE ARGS === */
t_bool					merge_args(t_token **tokens);
/* === SPLIT ARGS === */
int						count_args(t_parser *parser, int i);
char					**arg_split(char const *s);
t_bool					is_operator(char const *c, int no_space, int *len);
int						wordlen(char const *s, t_bool dquotes, t_bool squotes);
/* === SPLIT PIPES === */
t_command				*split_pipe(t_token *token, t_command *cmds,
							t_command *new, int i);
t_command				*create_cmd_list(t_command **cmds, t_token *tokens);
t_bool					is_command(t_arg_type arg_type);
t_bool					is_recognized_operator(t_operator operator);
t_bool					is_filename_or_limiter(t_arg_type arg_type);
int						str_and_operator(t_command *new, t_token *tokens);
/* ====== EXECUTOR ====== */
void					executor(t_mini *mini, t_command *current, int prev_fd,
							int count);
/* === PROCESS === */
void					parent_process(int *prev_fd, t_command *current);
void					child_process(t_command *current, int *prev_fd,
							t_mini *mini);
/* === HERE DOC CLOSE FD === */
void					close_child_heredoc_fd(t_command *cmds,
							t_command *current);
void					close_parent_heredoc_fd(t_command *current);
/* === DUP AND CREATE PIPE === */
void					duplicate_pipes(t_command *current, int *prev_fd,
							t_mini *mini);
int						create_pipe(t_command *current, int *prev_fd,
							t_mini *mini);
/* === EXECUTE COMMANDS === */
void					execute_cmd(t_command *current, char **envp,
							t_mini *mini);
void					get_path(char **envp, t_env *lst_env);
char					**get_unix_path(char **envp);
char					*copy_command(char *unix_path, char *commands);
int						*is_user_in_bin(t_mini *mini, t_command *current,
							char **envp);
void					is_path_a_directory(t_command *current, char **envp,
							t_mini *mini);
void					handle_no_exec(t_command *current, char **envp,
							t_mini *mini, int error);
/* === GET ENVP === */
int						get_envp_array(t_env *lst_env, char ***envp);
/* === HANDLE REDIRECTION === */
void					here_doc_redirection(t_command *current, t_mini *mini);
void					handle_redirection(t_command *current, t_mini *mini);
/* === HANDLE REDIRECTION UTILS === */
void					duplicate_fd(int oldfd, int newfd, t_mini *mini,
							t_command *current);
int						open_file(t_mini *mini, char *filename, int flags,
							mode_t mode);
void					check_directory(char *filename, t_mini *mini);
void					check_no_access(char *filename, int errno_code,
							t_mini *mini);
void					no_such_file(char *filename, t_mini *mini);
/* ====== HERE_DOC ====== */
char					*add_line_return(char *source, t_mini *mini);
int						setup_here_docs(t_mini *mini);
void					here_doc_exit(t_mini *mini, char *limiter, char *str,
							int *hd_pipe);
char					*here_doc_get_str(char *limiter, t_mini *mini,
							char *str, t_command *current);

#endif
