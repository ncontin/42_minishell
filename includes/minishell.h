/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:30:06 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/18 18:19:08 by aroullea         ###   ########.fr       */
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

extern int	g_signal_received;

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
	t_env				*lst_env;
	t_token				*tokens;
	t_command			*cmds;
}						t_mini;

/* === INIT === */
void		init_mini(t_mini *mini);
void		init_envp(t_mini *mini);
char		**get_envp_array(t_env *lst_env);

/* === BUILTINS === */
int			is_builtin(char *str);
void		execute_builtin(t_mini *mini, char **argv);
void		ft_pwd(t_mini *mini);
void		ft_echo(char **cmd_args, long long int *exit_code);
void		free_array(char **array);
int			ft_cd(t_mini *mini);
int			find_min_len(char *s1, char *s2);
void		print_export(t_env_node **sorted_envp_cp, char **args);
t_env_node	**copy_envp_list(t_env_node **envp_cp);
void		replace_env(t_env_node *env_to_replace, char *arg);
void		ft_env(t_mini *mini);
void		ft_export(t_mini *mini, char **cmd_args);
void		ft_unset(t_mini *mini, char **cmd_args);
void		ft_unset(t_mini *mini, char **cmd_args);
void		print_env(t_env_node **env_stack);
t_env_node	*find_last(t_env_node **my_envp);
int			find_equal(char *str);
char		*get_key(char *str);
char		*get_value(char *str);
void		ft_exit(t_mini *mini, char **cmd_args);
long long	ft_atoll(const char *nptr, int *overflow);

/* === SIGNAL === */
void		executor_signal(void);
void		child_signal(void);
void		handle_signals(void);
/* === FREEING === */
void		free_stack(t_env_node **my_envp);
void		free_array(char **array);
void		free_path(t_env *lst_env);
void		free_input(t_mini *mini);
void		free_exit(t_mini *mini);
void		free_token(t_token *token);
void		free_token_argument(t_token *token);
void		free_commands(t_command *cmds);
void		close_fd(int *pipe_fd);
/* === ERROR === */
void		error_msg(char *message, int error);
void		error_arg_split(t_mini *mini);
void		error_merge_args(t_mini *mini);
void		error_create_list(t_token *tokens, t_token *current);
void		error_split_pipe(t_mini *mini);
void		error_pid_executor(t_mini *mini, t_command *current, int *prev_fd);
void		error_dup2_executor(t_mini *mini, int error_code, int *prev_fd);
void		error_open_executor(t_mini *mini, int error_code);
void		get_str_error(t_mini *mini, int here_fd, char *new, char *limiter);
void		here_doc_error(char *str_error, int here_doc_pipe[2]);
/* ====== READLINE ====== */
void		line_read(t_mini *mini);
/* ====== PARSING ====== */
t_command	*parsing(t_mini *mini);
/* === CHECK OPERATOR === */
void		assign_operator(t_token *tokens);
void		assign_type_argument(t_token *tokens);
t_bool		is_even_quotes(char **tokens);
t_bool		is_valid_operator(char **args);
t_bool		is_valid_token(t_token *tokens);
/* === CREATE LIST === */
t_token		*create_list(char **tokens);
t_token		*init_new_list(t_token *head);
void		lst_add_new(t_token **head, t_token *new);
void		check_quotes(char *args, t_token *current);
int			get_size(char *args);
char		*rm_quotes(char *args, int size);
void		multi_str(char *args, int nb_strings, t_token **head, int i);
int			is_multi_strings(char *args, int i, t_bool dquote, t_bool squote);
/* === EXPANDER === */
void		expander(t_mini *mini);
char		*expand_exit_status(char *arg, t_mini *mini);
char		*expand_shell_vars(char *arg, t_mini *mini);
/* === MERGE ARGS === */
t_bool		merge_args(t_token **tokens);
/* === SPLIT ARGS === */
int			count_args(t_parser *parser);
char		**arg_split(char const *s);
t_bool		is_operator(char const *c, int no_space, int *len);
int			wordlen(char const *s, t_bool dquotes, t_bool squotes);
/* === SPLIT PIPES === */
t_command	*split_pipe(t_token *token, t_command *cmds, t_command *new, int i);
t_command	*create_cmd_list(t_command **cmds, t_token *tokens);
t_bool		is_command(t_arg_type arg_type);
t_bool		is_recognized_operator(t_operator operator);
t_bool		is_filename_or_limiter(t_arg_type arg_type);
int			str_and_operator(t_command *new, t_token *tokens);
/* ====== EXECUTOR ====== */
void		executor(t_mini *mini, t_command *current, int prev_fd, int count);
/* === DUP AND CREATE PIPE === */
void		duplicate_pipes(t_command *current, int *prev_fd, t_mini *mini);
int			create_pipe(t_command *current, int *prev_fd, t_mini *mini);
/* === EXECUTE COMMANDS === */
int			execute_builtin_parent(t_mini *mini, t_command *cmd);
void		execute_cmd(t_command *current, char **envp, t_mini *mini);
void		get_path(char **envp, t_env *lst_env);
char		**get_unix_path(char **envp);
char		*copy_command(char *unix_path, char *commands);
/* === HANDLE REDIRECTION === */
void		here_doc_redirection(t_command *current, t_mini *mini);
void		handle_redirection(t_command *current, t_mini *mini);
/* ====== HERE_DOC ====== */
char		*add_line_return(char *source, t_mini *mini);
int			setup_here_docs(t_mini *mini);
void		here_doc_exit(t_mini *mini, char *limiter, char *str, int *hd_pipe);
char		*here_doc_get_str(char *limiter, t_mini *mini, char *str,
				t_command *current);

#endif
