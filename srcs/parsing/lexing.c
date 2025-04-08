/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:34:54 by enrmarti          #+#    #+#             */
/*   Updated: 2025/04/08 14:38:49 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int is_redirection_char(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

//RETURNS THE NEXT TOKEN FOUND IN THE STRING
t_token *next_token(char **ps)
{
	t_token *t;
	char quote;
	char *start;

	*ps = skip_spaces(*ps);
	if (!**ps)
		return (NULL);
	start = *ps;
	t = NULL;
	if (is_redirection_char(**ps))
	{
		if ((**ps == '>' && *(*ps + 1) == '>') || (**ps == '<' && *(*ps + 1) == '<'))
		{
			t = create_token(ft_strndup(*ps, 2));
			*ps += 2;
		}
		else
		{
			t = create_token(ft_strndup(*ps, 1));
			(*ps)++;
		}
		return (t);
	}
	else
	{
		while (**ps && !is_space(**ps) && !is_redirection_char(**ps))
		{
			if (**ps == '\'' || **ps == '"')
			{
				quote = **ps;
				(*ps)++;
				while (**ps && (**ps) != quote)
					(*ps)++;
				if (**ps == quote)
					(*ps)++;
				else
				{
					printf("minishell: unclosed quotes found\n");
					return (NULL);
				}
			}
			else
				(*ps)++;
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
	// printf("\nBEFORE CLEAN:\n");
	// print_tokens(t);
	if (t != NULL)
		clean_tokens(t);
	shell->tokens = t;
}
