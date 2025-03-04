NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = srcs/main.c\
		srcs/parsing/parsing.c\
		srcs/utils/paress_utils.c		

OBJS = $(SRCS:.c=.o)
LIBFT = libft/libft.a
INCLUDES = -I include -I libft

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

$(LIBFT):
	@make -C libft

clean:
	rm -f $(OBJS)
	@make -C libft clean

fclean: clean
	rm -f $(NAME)
	@make -C libft fclean

re: fclean all
	