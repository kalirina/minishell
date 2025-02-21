/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:55:50 by enrmarti          #+#    #+#             */
/*   Updated: 2025/02/21 19:12:37 by enrmarti         ###   ########.fr       */
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

typedef struct  s_command
{
	char	*program_name;
	char	**args;
	char	**opts;
} t_command;

typedef struct	s_file
{
	char	*path;
	char	*permissions;
} t_file;

typedef enum    s_type
{
	NULL,
	PIPE,			//		|
	IN,				//		<
	OUT,			//		>
	HEREDOC,		//		<<
	OUT_APPEND		//		>>
} t_type;

typedef struct  s_separator
{
	t_type		type;
	t_command	*left;
	t_command	*right;
} t_separator;


#endif