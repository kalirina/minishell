/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:55:50 by enrmarti          #+#    #+#             */
/*   Updated: 2025/03/28 18:00:46 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

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

typedef struct	s_token
{
	char			*str;
	struct s_token	*next;
	char			quotes;
} t_token;

typedef struct s_redirection {
	char					*file;
	bool					append;
	struct s_redirection	*next;
} t_redirection;

typedef struct s_command {
	char				**args;
	t_redirection		*input;
	t_redirection		*output;
	struct s_command	*next;
} t_command;

typedef struct	s_shell
{
	t_token			*tokens;
	t_command		*cmd;
	char			**my_environ;
} t_shell;

void	lexer(t_shell *shell, char *line);
void	expand(t_shell	*shell);
void	parser(t_shell *shell);

//parsing utils
char	*skip_spaces(char *str);
bool	is_space(char str);
char	*ft_strndup(const char *s, size_t n);
t_redirection *add_redirection(t_redirection **head, char *file, bool append);
void	free_command(t_command *cmd);


t_token	*create_token(char *str);
t_token	*add_token(t_token **head, t_token *new);
t_token	*get_last_token(t_token **head);
t_token	*clean_tokens(t_token *tokens);

//test
void	print_tokens(t_token *t);

void setup_signal_handlers();

void	init_environ(t_shell *shell);
int		skip(char *line);
int		slash(char *line);
//execution
void	execute(t_shell *shell, t_command *cmd);
void	free_split(char **tab);
int		is_builtin(char **args);
int		is_valid_var(char *name);
//builtins
void	echo_cmd(char **args);
void	env_cmd(t_shell *shell);
void	pwd_cmd(void);
void	cd_cmd(char **args);
void	export_cmd(t_shell *shell,char **args);
char	*get_var(char *arg);
char	*get_val(char *arg);
void	add_new_env_var(t_shell *shell, int i, char *var, char *val);
void	update_env_var(t_shell *shell, int i, char *var, char *val);
void	unset_cmd(t_shell *shell, char **args);

#endif
