##
## Makefile for Amaze-D
##

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -std=c99 -I include -g3
LDFLAGS	= 

SRC		= src/main.c \
		  src/core/engine.c \
		  src/core/pathfinding.c \
		  src/core/room.c \
		  src/parser/parser.c \
		  src/parser/cleanup.c \
		  src/utils/string.c \
		  src/utils/io.c \
		  src/visual/display.c \
		  src/visual/stats.c

OBJ		= $(SRC:.c=.o)

NAME	= amaze-d

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
