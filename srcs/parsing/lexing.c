/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:34:54 by enrmarti          #+#    #+#             */
/*   Updated: 2025/03/28 17:41:51 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int is_redirection_char(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

int	find_type(char *pt)
{
	if (!pt)
		return (0);
	if (ft_strncmp(pt, "|", 1) == 0)
		return (3);
	if (ft_strncmp(pt, "<", 1) == 0)
		return (4);
	if (ft_strncmp(pt, ">", 2) == 0)
		return (5);
	if (ft_strncmp(pt, ">>", 2) == 0)
		return (6);
	if (ft_strncmp(pt, "<<", 2) == 0)
		return (7);
	if (ft_strncmp(pt, ";", 1) == 0)
		return (8);
	else
		return (1);
}

// t_token *next_token(char **ps)
// {
//     t_token *t;
//     char quote;
//     char *start;

// 	*ps = skip_spaces(*ps);
// 	if (!**ps)
// 		return (NULL);
// 	start = *ps;
// 	t = NULL;
// 	if (is_redirection_char(**ps)) {
// 		if ((**ps == '>' && *(*ps + 1) == '>') || (**ps == '<' && *(*ps + 1) == '<'))
// 		{
// 			t = create_token(ft_strndup(*ps, 2));
// 			*ps += 2;
// 		}
// 		else
// 		{
// 			t = create_token(ft_strndup(*ps, 1));
// 			(*ps)++;
// 		}
// 		return (t);
// 	}
// 	else
// 	{
// 		while (**ps && !is_space(**ps) && !is_redirection_char(**ps)) {
// 			if (**ps == '\'' || **ps == '"') {
// 				quote = **ps;
// 				(*ps)++;
// 				while (**ps && (**ps) != quote)
// 					(*ps)++;
// 				if (**ps == quote)
// 					(*ps)++;
// 				else
// 				{
// 					printf("minishell: unclosed quotes found\n");
// 					return NULL; //Return NULL because of unclosed quotes
// 				}
// 			}
// 			else
// 				(*ps)++;
// 		}
// 		if (*ps > start)
// 			t = create_token(ft_strndup(start, *ps - start));
// 		else
// 			return NULL;
// 	}

// 	return t;
// }

//test
t_token *next_token(char **ps) {
    t_token *t;
    char quote;
    char *start;

    *ps = skip_spaces(*ps);
    if (!**ps)
        return (NULL);

    start = *ps;
    t = NULL; // Initialize t to NULL

    if (is_redirection_char(**ps)) {
        // Handle redirection operators
        if ((**ps == '>' && *(*ps + 1) == '>') || (**ps == '<' && *(*ps + 1) == '<')) {
            // Handle ">>" and "<<"
            t = create_token(ft_strndup(*ps, 2));
            *ps += 2;
        } else {
            // Handle ">", "<", and "|"
            t = create_token(ft_strndup(*ps, 1));
            (*ps)++;
        }
        return t; // Return the redirection token
    } else {
        // Handle regular words and quoted strings
        while (**ps && !is_space(**ps) && !is_redirection_char(**ps)) {
            if (**ps == '\'' || **ps == '"') {
                quote = **ps;
                (*ps)++;
                while (**ps && (**ps) != quote)
                    (*ps)++;
                if (**ps == quote)
                    (*ps)++;
                else {
                    fprintf(stderr, "minishell: unclosed quotes found\n");
                    return NULL; //Return NULL because of unclosed quotes
                }
            } else {
                (*ps)++;
            }
        }
        if (*ps > start)
          t = create_token(ft_strndup(start, *ps - start));
        else
          return NULL;
    }

    return t;
}


//READS THE COMMAND AND DIVIDES IT IN TOKENS
void	lexer(t_shell *shell, char *line)
{
	t_token	*t;
	t_token *new;

	t = NULL;
	new = next_token(&line);
	while (new != NULL)
	{
		t = add_token(&t, new);
		new = next_token(&line);
	}
	if (t != NULL)
		clean_tokens(t);
	shell->tokens = t;
	//print_tokens(t);
}
