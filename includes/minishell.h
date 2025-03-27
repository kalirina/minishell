/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:55:50 by enrmarti          #+#    #+#             */
/*   Updated: 2025/03/27 03:30:18 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../srcs/libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <string.h>
# include <errno.h>

# define MAX_TOKEN 100

# define CMD 1			// commands and args
//# define VAR 2			// $var
# define PIPE 3			// |
# define INPUT 4		// <
# define OUTPUT 5		// >
# define APPEND 6		// >>
# define HEREDOC 7		// <<
//# define SEMICOLON 8	// ;
//# define S_QUOTE 9		// '
//# define D_QUOTE 10		// "

// typedef enum e_node
// {
// 	WORD,
// 	PIPE,			//|
// 	OUT, 			//>
// 	D_OUT,	 		//>>
// 	IN,				//<
// 	HEREDOC, 		//<<
// } t_node_type;

typedef struct s_token
{
	int					index;
	char				*str;
	struct s_token		*prev;
	struct s_token		*next;
}	t_token;

typedef struct s_command
{
	int					type;
	char				**args;
	char				*input;
	char				*output;
	bool				append;
	struct s_command	*next;
}	t_command;

typedef struct s_shell
{
	t_token				*tokens;
	t_command			*cmd;
	char				**my_environ;
	int					exit_status;
}	t_shell;

void	lexer(t_shell *shell, char *line);
void	parser(t_shell *shell);

//parsing utils
char	*skip_spaces(char *str);
bool	is_space(char str);
char	*ft_strndup(const char *s, size_t n);

t_token	*add_token(t_token **head, t_token *new);
t_token	*get_last_token(t_token **head);

void	setup_signal_handlers(void);
//utils
void	init_environ(t_shell *shell);
int		skip(char *line);
int		slash(char *line);
int		print_error(char *cmd, char *arg, char *msg);
char	*get_env_var_value(char **my_environ, const char *var_name);
int		find_env_var_index(char **my_environ, const char *var);
int		set_env_var(t_shell *shell, char *var, char *val);
char	*get_var(char *arg);
char	*get_val(char *arg);
void	add_new_env_var(t_shell *shell, int i, char *var, char *val);
void	update_env_var(t_shell *shell, int i, char *var, char *val);
//execution
void	execute(t_shell *shell);
void	free_split(char **tab);
int		is_builtin(char **args);
int		is_valid_var(char *name);
//builtins
int		echo_cmd(t_shell *shell);
int		env_cmd(t_shell *shell);
int		pwd_cmd(void);
int		cd_cmd(t_shell *shell);
int		export_cmd(t_shell *shell, char **args);
int		unset_cmd(t_shell *shell, char **args);

#endif
