/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:55:50 by enrmarti          #+#    #+#             */
/*   Updated: 2025/02/21 15:33:20 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdlib.h>
#include <stdio.h>


typedef struct  s_command
{
    char    *command;
    char    **args;
    char    *opt;
} t_command;

typedef enum    s_types
{
    PIPE,
    IN,
    OUT,
    HEREDOC,
    OUT_APPEND
} t_types;

typedef struct  s_separator
{
    t_types     type;
    t_command   *left;
    t_command   *right;
} t_separator;



#endif