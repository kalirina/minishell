NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = srcs/main.c\
		srcs/lexing/lexing.c\
		srcs/lexing/lexing_utils.c\
		srcs/parsing/expand.c\
		srcs/parsing/parse_utils.c\
		srcs/utils/list_utils.c\
		srcs/parsing/parsing.c\
		srcs/utils/signals.c\
		srcs/builtins/cd.c\
		srcs/builtins/echo.c\
		srcs/builtins/env.c\
		srcs/builtins/export.c\
		srcs/builtins/pwd.c\
		srcs/builtins/unset.c\
		srcs/exec/exec_utils.c\
		srcs/exec/exec.c\
		srcs/utils/main_utils.c

OBJS = $(SRCS:.c=.o)
LIBFT = includes/libft/libft.a
INCLUDES = -I include -I libft

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

$(LIBFT):
	@make -C includes/libft

clean:
	rm -f $(OBJS)
	@make -C includes/libft clean

fclean: clean
	rm -f $(NAME)
	@make -C includes/libft fclean

re: fclean all
