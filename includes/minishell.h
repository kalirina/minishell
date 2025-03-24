/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:55:50 by enrmarti          #+#    #+#             */
/*   Updated: 2025/03/23 23:53:13 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include "../libft/libft.h"

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
	struct s_token	*prev;
	struct s_token	*next;
} t_token;

typedef struct	s_command
{
	int					type;
	char				**args;
	char				*input;
	char				*output;
	bool				append;
	struct s_command	*next;
} t_command;

typedef struct	s_shell
{
	t_token			*tokens;
	t_command		*cmd;
} t_shell;

void	lexer(t_shell *shell, char *line);
void	parser(t_shell *shell);

//parsing utils
char	*skip_spaces(char *str);
bool	is_space(char str);
char	*ft_strndup(const char *s, size_t n);

t_token	*add_token(t_token **head, t_token *new);
t_token	*get_last_token(t_token **head);

void setup_signal_handlers();

#endif

