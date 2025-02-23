/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:55:50 by enrmarti          #+#    #+#             */
/*   Updated: 2025/02/23 22:29:02 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/stat.h>


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

// builtins
int		cd_cmd(char *path);
char	*join_components(char **components);

#endif
