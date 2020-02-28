CC = gcc
CFLAGS = -Wall -Werror -Wextra

SOURCES = ./libft.h
NAME = libft.a

$(NAME):
	$(CC) $(CFLAGS) -c *.c
	ar rcs $(NAME) *.o
	ranlib $(NAME)

.PHONY: all clean fclean re

all: $(NAME)

clean:
	rm -f *.o

fclean:	clean
	rm -f $(NAME)

re: fclean all
