/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:55:50 by enrmarti          #+#    #+#             */
/*   Updated: 2025/03/19 23:06:00 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "../srcs/libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

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
	int				index;
	char			*str;
	struct s_token	*next;
} t_token;

typedef struct	s_node
{
	int				type;
	char			**args;
	struct s_node	*left;
	struct s_node	*right;
} t_node;

typedef struct	s_shell
{
	t_token		*tokens;
	t_node		*ast;
	char		**my_environ;
} t_shell;

void	lexer(t_shell *shell, char *line);
void	parser(t_shell *shell);

//parsing utils
char	*skip_spaces(char *str);
bool	is_space(char str);
char	*ft_strndup(const char *s, size_t n);

t_token	*add_token(t_token **head, t_token *new);

void	init_environ(t_shell *shell);
void	sync_my_environ(t_shell *shell);
void	execute(t_shell *shell, char **args);
//builtins
void	echo_cmd(char **args);
void	env_cmd(t_shell *shell);
void	pwd_cmd(void);
void	cd_cmd(char **args);
void	export_cmd(t_shell *shell,char **args);

#endif
