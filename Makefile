CC = gcc
NAME = fillit
C_FLAGS = -Wall -Wextra -Werror
C_FILES = main.c fillit.c solve_square.c check_invalids.c
C_OBJ = $(C_FILES:.c=.o)
DEBUG_NAME = debug
DEBUG_FILES = debug_funcs.c
DEBUG_OBJ = $(DEBUG_FILES:.c=.o)
LIBFT = libft/libft.a

$(NAME): $(C_OBJ)
	$(CC) $(C_FLAGS) -o $(NAME) $(C_OBJ) $(LIBFT)

$(DEBUG_NAME):
	$(CC) $(C_FLAGS) -g -o $(DEBUG_NAME) $(C_FILES) $(DEBUG_FILES) $(LIBFT)

.PHONY: all clean fclean re

all: $(NAME)

clean:
	make clean -C libft
	rm -f $(C_OBJ) $(DEBUG_OBJ)

fclean: clean
	make fclean -C libft
	rm -f $(NAME) $(DEBUG_NAME)

re: fclean all