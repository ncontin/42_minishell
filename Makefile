NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

RM = rm -f
OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
LIBRARY = includes/libft/libft.a
INCLUDES = -I./includes -I./includes/libft

SRC = src/main.c src/readline.c

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	make all -C includes/libft
	$(CC) $(OBJ) $(CFLAGS) $(INCLUDES) $(LIBRARY) -o $(NAME) -lreadline

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) -r $(OBJ_DIR)
	make clean -C includes/libft

fclean: clean
	$(RM) $(NAME)
	make fclean -C includes/libft

re: fclean all

.PHONY: all bonus clean fclean re
