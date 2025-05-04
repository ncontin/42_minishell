/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:30:06 by aroullea          #+#    #+#             */
/*   Updated: 2025/05/04 12:09:16 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// 42 Library
# include "libft/libft.h"

// Standard C Library Functions
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

// File & Directory Operations
# include <dirent.h>
# include <limits.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

// Process & Signal Handling
# include <fcntl.h>
# include <signal.h> 

// Readline (Interactive Input)
# include <readline/history.h>
# include <readline/readline.h> 

// Errno
# include <errno.h>

extern int	g_signal_received;

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef enum e_quotes
{
	NO_QUOTES,
	SINGLE,
	DOUBLE
}	t_quotes;

typedef enum e_operator
{
	NONE,
	OUTPUT,
	INPUT,
	APPEND,
	HEREDOC,
	PIPE
}	t_operator;

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
}	t_arg_type;

typedef struct s_env_node
{
	char				*key;
	char				*value;
	struct s_env_node	*next;
}	t_env;

typedef struct s_parser
{
	char const			*s;
	int					count;
	char				quote_char;
	t_bool				in_word;
	t_bool				in_quotes;
}	t_parser;

typedef struct s_token
{
	char				*argument;
	t_quotes			quotes;
	t_bool				linked;
	t_bool				hd_expand;
	t_operator			operator;
	t_arg_type			arg_type;
	struct s_token		*next;
	struct s_token		*prev;
}	t_token;

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
}	t_command;

typedef struct s_mini
{
	int					error;
	char				*input;
	char				*hd_input;
	long long int		exit_code;
	int					expanded;
	t_env				*envp_cp;
	t_command			*cmds;
}	t_mini;

/* === INIT === */
void		init_envp(t_mini *mini, char **envp);

/* === BUILTINS === */
int			is_builtin(char *str);
void		execute_builtin(t_mini *mini, char **argv);
void		ft_pwd(t_mini *mini);
void		ft_echo(char **cmd_args, long long int *exit_code);
void		ft_cd(t_mini *mini, char *path);
char		*handle_home(t_mini *mini, char *pwd);
void		handle_previous_path(t_mini *mini, char *pwd);
int			update_old_pwd(t_env *env_stack, t_mini *mini);
int			check_cd_path(char *path);
char		*get_env_value(t_env *envp_cp, char *key);
int			update_pwd(t_env *env_stack, t_mini *mini);
int			get_or_create_pwd(t_env *current, t_mini *mini,
				char *key_name, char *pwd);
int			find_min_len(char *s1, char *s2);
void		print_export(t_env *sorted_envp_cp);
t_env		*copy_envp_list(t_env *envp_cp, t_mini *mini);
int			replace_env(t_env *env_to_replace, char *arg);
void		ft_env(t_mini *mini, char **cmd_args);
void		ft_export(t_mini *mini, char **cmd_args);
void		ft_unset(t_mini *mini, char **cmd_args);
void		ft_unset(t_mini *mini, char **cmd_args);
void		print_env(t_env *env_stack);
int			find_equal(char *str);
char		*get_key(char *str, int *err_code);
char		*get_value(char *str, int *err_code);
void		ft_exit(t_mini *mini, char **cmd_args);
long long	ft_atoll(const char *nptr, int *overflow);
char		*del_spaces(char *str);
int			check_digit(char *str);
int			is_double_dash(char **cmd_args);
t_env		*check_existing_env(t_env *envp_cp, char *arg);
int			add_export_env(t_env *lst_env, char *arg, t_mini *mini);
void		swap_nodes(t_env *current, t_env *temp);
void		sort_env(t_env *envp_cp);
void		print_id_error(t_mini *mini, char *arg);
int			is_valid_option(t_mini *mini, char **cmd_args);
int			is_valid_identifier(t_mini *mini, char *arg);
int			join_env_value(t_env *env_to_replace, char *arg, t_mini *mini);
/* === SIGNAL === */
void		executor_signal(void);
void		child_signal(void);
void		handle_signals(void);
/* === FREEING === */
void		free_stack(t_env *my_envp);
void		free_array(char **array);
void		free_path(t_env *lst_env);
void		free_input(t_mini *mini);
void		free_exit(t_mini *mini);
void		free_token(t_token *token);
void		free_token_argument(t_token *token);
void		free_commands(t_command *cmds);
void		clean_exit(t_mini *mini, char **envp, int exit_code);
void		close_fd(int *pipe_fd);
/* === ERROR === */
void		error_msg(char *message, int error);
void		error_arg_split(t_mini *mini);
void		error_merge_args(t_mini *mini);
void		error_create_list(t_token **tokens, t_token *current);
void		error_split_pipe(t_mini *mini);
void		error_pid_executor(t_mini *mini, t_command *current, int *prev_fd);
void		error_dup2_executor(t_mini *mini, int error_code, int *prev_fd);
void		error_open_executor(t_mini *mini, int error_code);
void		print_executor_error(char *msg, char *arg);
void		error_path(t_mini *mini, char **envp, int err_code, t_command *cmd);
void		print_file_error(char *filename, char *message);
void		get_str_error(t_mini *mini, int here_fd, char *new, char *limiter);
void		print_error_cd(char *msg, char *arg);
void		print_error_chdir(char *path, char *pwd, t_mini *mini);
void		here_doc_error(char *str_error, int here_doc_pipe[2]);
void		copy_env_error(t_env *head);
void		ft_envp_error(t_mini *mini);
void		copy_env_node_error(t_env *sorted_envp_cp, t_mini *mini);
void		handle_join_env_error(char *str1, char *str2);
void		print_id_error(t_mini *mini, char *arg);
void		handle_add_export_error(t_env *env, char *key);
void		expander_error(t_mini *mini, int *err_code);
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
int			is_tilde(t_mini *mini, t_token *tokens);
void		is_dollar_alone(t_token *tokens);
int			check_dollar(t_mini *mini, t_token *tokens);
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
int			expander(t_mini *mini, t_token **tokens, t_token *current,
				int *err_code);
char		*expand_exit_status(char *arg, t_mini *mini);
void		free_three(char *a, char *b, char *c);
char		*get_current_value(char *value);
char		*handle_strjoin(char *s1, char *s2);
char		*handle_substr(char *src, int start, size_t len);
char		*expand_shell_vars(char *arg, t_mini *mini, int *err_code);
char		*get_env_var(char *full_str, t_env *current, int i,
				int *err_code);
char		*no_args(char *full_str, int i, int *err_code);
int			split_words(t_mini *mini, t_token **tokens, int *err_code);
int			find_word_len(char *arg, int len);
int			get_array_size(char **array);
int			has_space(char *str);
t_token		*create_token(char *arg);
int			add_new_token(t_token *token, char *word, t_token *next_og);
int			is_dollar(t_token **tokens);
int			is_nl_char(t_token **tokens);
void		replace_tokens(t_token **tokens);
void		advance_token(t_token **tokens, t_token **current);
int			handle_nl_expand(t_token **tokens);
/* === MERGE ARGS === */
t_bool		merge_args(t_token **tokens);
/* === SPLIT ARGS === */
int			count_args(t_parser *parser, int i);
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
/* === PROCESS === */
void		update_underscore(t_command *cmd, t_env *envp_cp,
				t_mini *mini);
void		parent_process(int *prev_fd, t_command *current);
void		child_process(t_command *current, int *prev_fd, t_mini *mini);
void		free_and_exit(t_mini *mini, char **unix_path, char **envp);
/* === HERE DOC CLOSE FD === */
void		close_child_heredoc_fd(t_command *cmds, t_command *current);
void		close_parent_heredoc_fd(t_command *current);
/* === DUP AND CREATE PIPE === */
void		duplicate_pipes(t_command *current, int *prev_fd, t_mini *mini);
int			create_pipe(t_command *current, int *prev_fd, t_mini *mini);
/* === EXECUTE COMMANDS === */
void		execute_cmd(t_command *current, char **envp, t_mini *mini);
void		get_path(char **envp, t_env *lst_env);
char		**get_unix_path(char **envp);
char		*copy_command(char *unix_path, char *commands);
int			is_user_in_bin(t_mini *mini, t_command *current, char **envp);
void		is_path_a_directory(t_command *current, char **envp, t_mini *mini);
void		handle_no_exec(t_command *current, char **envp, t_mini *mini,
				int error);
void		update_underscore_path(char *path, t_env *envp_cp,
				t_mini *mini);
/* === GET ENVP === */
int			get_envp_array(t_env *lst_env, char ***envp);
/* === HANDLE REDIRECTION === */
void		here_doc_redirection(t_command *current, t_mini *mini);
void		handle_redirection(t_command *current, t_mini *mini);
/* === HANDLE REDIRECTION UTILS === */
void		duplicate_fd(int oldfd, int newfd, t_mini *mini,
				t_command *current);
int			open_file(t_mini *mini, char *filename, int flags, mode_t mode);
void		check_directory(char *filename, t_mini *mini);
void		check_no_access(char *filename, int errno_code, t_mini *mini);
void		no_such_file(char *filename, t_mini *mini);
/* ====== HERE_DOC ====== */
char		*add_line_return(char *source, t_mini *mini);
int			setup_here_docs(t_mini *mini);
void		here_doc_exit(t_mini *mini, char *limiter, char *str, int *hd_pipe);
char		*here_doc_get_str(char *limiter, t_mini *mini, char *str,
				t_command *current);
void		expand_error(t_mini *mini, char *limiter, char *str);

#endif
