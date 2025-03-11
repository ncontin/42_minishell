NAME = minishell 

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

RM = rm -f
OBJ_DIR = ./obj
LIB_DIR = ./libft
LIB_NAME = libft.a
LIBRARY = -L./libft -lft
INCLUDE = -I./libft

SRC = sources/main.c sources/readline.c

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(LIB_DIR)/$(LIB_NAME) $(NAME)

$(LIB_DIR)/$(LIB_NAME):
	make -C $(LIB_DIR)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBRARY) -lreadline

clean:
	$(RM) -r $(OBJ_DIR)
	make -C $(LIB_DIR) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIB_DIR) fclean

re: fclean all

.PHONY: all bonus clean fclean re
