NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

RM = rm -f

OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
SRC =	src/main.c\
		src/readline.c\
		src/path.c\
		$(SRC_BUILTINS)\
		$(SRC_CLEANUP)\
		$(SRC_ERRORS)\
		$(SRC_PARSING)\
		$(SRC_ENVS)\

SRC_BUILTINS =	src/builtins/builtins.c\
				src/builtins/pwd.c\
				src/builtins/echo.c\
				src/builtins/cd.c\
				src/builtins/env.c\
				src/builtins/export.c\
				src/builtins/unset.c\
				src/builtins/builtins_utils.c\
				src/builtins/export_utils.c\

SRC_CLEANUP =	src/cleanup/free_array.c\
				src/cleanup/free_struct.c\
				src/cleanup/free_stack.c\

SRC_ERRORS = 	src/errors/error.c\

SRC_PARSING = 	src/parsing/args_split.c\
				src/parsing/parsing.c\
				src/parsing/args_split_utils.c\
				src/parsing/args_count.c \
				src/parsing/args_wordlen.c\

SRC_ENVS =		src/envs/envp.c\
				src/envs/envs_utils.c\

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
