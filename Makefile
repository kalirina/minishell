NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = srcs/main.c\
		srcs/parsing/lexing.c\
		srcs/parsing/parse_utils.c\
		srcs/utils/list_utils.c\
		srcs/parsing/parsing.c\
		srcs/utils/signals.c\
		srcs/builtins/cd.c\
		srcs/builtins/echo.c\
		srcs/builtins/exit.c\
		srcs/builtins/env.c\
		srcs/builtins/export.c\
		srcs/builtins/pwd.c\
		srcs/builtins/unset.c\
		srcs/execution/exec_utils.c\
		srcs/execution/exec.c\
		srcs/builtins/input_utils.c\
		srcs/builtins/env_utils.c\
		srcs/builtins/export_utils.c

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
