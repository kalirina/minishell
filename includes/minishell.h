/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:55:50 by enrmarti          #+#    #+#             */
/*   Updated: 2025/03/04 13:58:04 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include "../libft/libft.h"

# define MAX_TOKEN 100

# define INVALID 0
# define WORD 1			// commands and args
# define VAR 2		// $var
# define PIPE 3			// |
# define INPUT 4		// <
# define OUTPUT 5		// >
# define APPEND 6		// >>
# define HEREDOC 7		// <<
# define SEMICOLON 8	// ;
 
typedef struct	s_token
{
	char		*value;
	int			type;
} t_token;

typedef struct	s_node
{
	int				type;
	char			*value;
	struct t_node	*left;
	struct t_node	*right;
} t_node;

typedef struct	s_shell
{
	t_token		*tokens;
	t_node		*ast;
} t_shell;

void	process_input(t_shell *shell, char *ps);


//parsing utils
char	*skip_spaces(char *str);
bool	is_space(char str);
char	*ft_strndup(const char *s, size_t n);


#endif