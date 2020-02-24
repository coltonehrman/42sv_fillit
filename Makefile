CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = fillit
SRC = fillit.c
LIBFT = libft/libft.a
OBJ = $(SRC:.c=.o)

LDFLAGS = -lGL -lglut -lpng -lz -lm
INCLUDES = libft/libft.a

.PHONY: all clean

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBFT)

clean:
	rm -f $(OBJ) $(NAME)
