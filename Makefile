NAME = fillit
CC = gcc
CFLAGS = -Wall -Wextra -Werror
CFILES = main.c fillit.c solve_square.c
DEBUG_NAME = debug
DEBUG_FILES = debug_funcs.c
LIBFT = libft/libft.a
OBJ = $(CFILES:.c=.o)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBFT)

$(DEBUG_NAME): $(OBJ) $(DEBUG_FILES:.c=.o)
	$(CC) $(CFLAGS) -o $(DEBUG_NAME) $^ $(LIBFT)

.PHONY: all clean

all: $(NAME)

clean:
	rm -f $(OBJ) $(NAME) $(DEBUG_NAME)

fclean:
	rm -f $(NAME) $(DEBUG_NAME)
