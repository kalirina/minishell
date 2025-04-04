NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = srcs/main.c\
		srcs/debug.c\
		srcs/parsing/lexing.c\
		srcs/parsing/lexing_utils.c\
		srcs/parsing/parse_utils.c\
		srcs/parsing/parsing.c\
		srcs/parsing/expand.c\
		srcs/parsing/heredoc.c\
		srcs/utils/list_utils.c\
		srcs/utils/signals.c\
		srcs/builtins/cd.c\
		srcs/builtins/echo.c\
		srcs/builtins/env_utils.c\
		srcs/builtins/export_utils.c\
		srcs/builtins/input_utils.c\
		srcs/builtins/exit.c\
		srcs/builtins/env.c\
		srcs/builtins/export.c\
		srcs/builtins/pwd.c\
		srcs/builtins/unset.c\
		srcs/execution/exec_utils.c\
		srcs/execution/exec.c

OBJS = $(SRCS:.c=.o)
LIBFT = srcs/libft/libft.a
INCLUDES = -I include -I libft

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

$(LIBFT):
	@make -C srcs/libft

clean:
	rm -f $(OBJS)
	@make -C  srcs/libft clean

fclean: clean
	rm -f $(NAME)
	@make -C  srcs/libft fclean

re: fclean all
