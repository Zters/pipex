NAME = pipex
SRCS = main.c utils.c utils2.c
OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror
CC = gcc
all: $(NAME)
	
$(NAME):$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
.c.o: 
	$(CC) $(CFLAGS) $< -c  -o $@
clean:
		rm -rf $(OBJS)
fclean: clean
	rm -rf $(NAME)
