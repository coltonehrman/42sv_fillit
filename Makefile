CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = fillit
SRC = main.c fillit.c solve_square.c
DEBUG = debug_funcs.c
LIBFT = libft/libft.a
OBJ = $(SRC:.c=.o)

LDFLAGS = -lGL -lglut -lpng -lz -lm
INCLUDES = libft/libft.a

.PHONY: all clean

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBFT)

debug: $(OBJ) $(DEBUG:.c=.o)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBFT)

clean:
	rm -f $(OBJ) $(NAME)
