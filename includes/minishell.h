/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:55:50 by enrmarti          #+#    #+#             */
/*   Updated: 2025/02/25 18:10:21 by enrmarti         ###   ########.fr       */
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

# define MAX_TOKEN 100

# define INVALID 0
# define CMD 1
# define OPT 2
# define ARG 3
# define PIPE 4			// |
# define INPUT 5		// <
# define OUTPUT 6		// >
# define APPEND 7		// >>
# define REDIRECT 8		// <<
# define SEPARATOR 9	// ;
 
typedef struct	s_token
{
	char		*str;
	int			index;
	int			type;
	t_token		*prev;
	t_token		*next;
} t_token;


typedef struct	s_minish
{
	
} t_minish;

#endif