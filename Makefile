NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = srcs/main.c\
		srcs/lexing/lexing.c\
		srcs/utils/parse_utils.c\
		srcs/utils/list_utils.c\
		srcs/parsing/parsing.c\
		srcs/utils/signals.c\
		srcs/builtins/cd.c\
		srcs/builtins/echo.c\
		srcs/builtins/env.c\
		srcs/builtins/export.c\
		srcs/builtins/pwd.c\
		srcs/builtins/unset.c\
		srcs/exec_utils.c\
		srcs/exec.c\
		srcs/utils.c

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
