NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

RM = rm -f

OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
SRC =	src/main.c\
		src/path.c\
		$(SRC_BUILTINS)\
		$(SRC_CLEANUP)\
		$(SRC_ERRORS)\
		$(SRC_PARSING)\
		$(SRC_READLINE)\

SRC_BUILTINS =	src/builtins/builtins.c\
				src/builtins/pwd.c\
				src/builtins/echo.c\
				src/builtins/cd.c\
				src/builtins/env.c\

SRC_CLEANUP =	src/cleanup/free.c\

SRC_ERRORS = 	src/errors/error.c\

SRC_PARSING =	src/parsing/split_args/args_count.c\
				src/parsing/split_args/args_split.c\
				src/parsing/split_args/args_split_utils.c\
				src/parsing/split_args/args_wordlen.c\
				src/parsing/create_list/create_list.c\
				src/parsing/create_list/create_list_utils.c\
				src/parsing/parsing.c\
				src/parsing/even_quotes.c\

SRC_READLINE =  src/readline/readline.c\

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
	@echo "$(GREEN)$(NAME) successfully built!"

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
