NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -f

OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
SRC =	src/main.c\
		$(SRC_BUILTINS)\
		$(SRC_CLEANUP)\
		$(SRC_ERRORS)\
		$(SRC_PARSING)\
		$(SRC_READLINE)\
		$(SRC_INIT)\
		$(SRC_SIGNALS)\
		$(SRC_EXECUTOR)\

SRC_BUILTINS =	src/builtins/builtins.c\
				src/builtins/pwd.c\
				src/builtins/echo.c\
				src/builtins/env.c\
				src/builtins/unset.c\
				src/builtins/builtins_utils.c\
				src/builtins/exit.c\
				src/builtins/exit_utils.c\
				src/builtins/ft_atoll.c\
				src/builtins/cd/cd.c\
				src/builtins/cd/cd_utils.c\
				src/builtins/cd/get_pwd.c\
				src/builtins/cd/previous_path.c\
				src/builtins/export/export.c\
				src/builtins/export/export_utils.c\
				src/builtins/export/add_env.c\
				src/builtins/export/print.c\
				src/builtins/export/copy_env.c\
				src/builtins/export/joined_env.c\
				src/builtins/export/replace_env.c\

SRC_CLEANUP =	src/cleanup/free_stack.c\
				src/cleanup/free_exit.c\
				src/cleanup/free_input.c\
				src/cleanup/free_array.c\
				src/cleanup/free_token.c\
				src/cleanup/free_commands.c\
				src/cleanup/close_fd.c\


SRC_ERRORS = 	src/errors/parsing_error.c\
				src/errors/executor_error.c\
				src/errors/redirection_error.c\
				src/errors/cd_error.c\
				src/errors/init_error.c\
				src/errors/export_error.c\
				src/errors/expander_error.c\

SRC_PARSING =	src/parsing/split_args/args_count.c\
				src/parsing/split_args/args_split.c\
				src/parsing/split_args/args_split_utils.c\
				src/parsing/split_args/args_wordlen.c\
				src/parsing/create_list/create_list.c\
				src/parsing/create_list/create_list_utils.c\
				src/parsing/create_list/create_list_init.c\
				src/parsing/create_list/handle_multi_str.c\
				src/parsing/create_list/is_multi_strings.c\
				src/parsing/check_operator/assign_operator.c\
				src/parsing/check_operator/is_valid_token.c\
				src/parsing/check_operator/assign_type_argument.c\
				src/parsing/check_operator/is_even_quotes.c\
				src/parsing/check_operator/is_valid_operator.c\
				src/parsing/check_operator/is_tilde.c\
				src/parsing/check_operator/is_dollar_alone.c\
				src/parsing/check_operator/check_dollar.c\
				src/parsing/merge_args/merge_args.c\
				src/parsing/split_pipes/str_and_operator.c\
				src/parsing/split_pipes/split_pipes.c\
				src/parsing/split_pipes/split_pipes_init.c\
				src/parsing/split_pipes/split_pipe_utils.c\
				src/parsing/parsing.c\
				$(SRC_EXPANDER)\

SRC_EXPANDER = 	src/parsing/expander/expander.c\
				src/parsing/expander/expander_utils.c\
				src/parsing/expander/utils.c\
				src/parsing/expander/split_words.c\
				src/parsing/expander/split_words_utils.c\
				src/parsing/expander/get_envp/shell_vars.c\
				src/parsing/expander/get_envp/get_environment_var.c\
				src/parsing/expander/get_envp/get_environment_utils.c\
				src/parsing/expander/get_envp/no_environment_var.c\
				src/parsing/expander/get_envp/exit_status.c\

SRC_READLINE =  src/readline/readline.c\

SRC_INIT =		src/init/envp_init.c\

SRC_EXECUTOR =	src/executor/executor.c\
				src/executor/process.c\
				src/executor/here_doc_close_fd.c\
				src/executor/handle_redirection.c\
				src/executor/handle_redirection_utils.c\
				src/executor/execute_commands.c\
				src/executor/execute_commands_utils.c\
				src/executor/dup_create_pipe.c\
				src/executor/path.c\
				src/executor/get_envp.c\
				src/executor/update_underscore.c\
				src/executor/here_doc/setup_here_docs.c\
				src/executor/here_doc/here_doc_utils.c\
				src/executor/here_doc/here_doc_get_str.c\

SRC_SIGNALS = 	src/signals/signals.c\
				src/signals/executor_signal.c\

LIBRARY = includes/libft/libft.a
INCLUDES = -I./includes -I./includes/libft

# Define colors for terminal output
GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
BLUE = \033[0;34m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(YELLOW)Building libft...$(RESET)"
	@make -s -C includes/libft all
	@echo "$(YELLOW)Linking $(NAME)...$(RESET)"
	@$(CC) $(OBJ) $(CFLAGS) $(INCLUDES) $(LIBRARY) -o $(NAME) -lreadline
	@echo "$(GREEN)$(NAME) successfully built!$(RESET)"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(BLUE)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@$(RM) -r $(OBJ_DIR)
	@make -s -C includes/libft clean

fclean: clean
	@echo "$(RED)Removing $(NAME)...$(RESET)"
	@$(RM) $(NAME)
	@make -s -C includes/libft fclean

re: fclean all

verbose:
	$(MAKE) all

.PHONY: all bonus clean fclean re
