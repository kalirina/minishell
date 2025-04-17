/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:34:54 by enrmarti          #+#    #+#             */
/*   Updated: 2025/04/17 16:34:35 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_redirection_char(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

//SKIPS THE REDIRECTION FOUND IN THE LINE AND RETURNS A TOKEN FOR IT
t_token	*redirection_found(char **ps)
{
	t_token	*t;

	if ((**ps == '>' && *(*ps + 1) == '>')
		|| (**ps == '<' && *(*ps + 1) == '<'))
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

//READS THE TOKEN AND RETURNS IT
t_token	*default_token(char **ps)
{
	char	quote;
	char	*start;

	start = *ps;
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
				return (printf("minishell: unclosed quotes found\n"), NULL);
		}
		else
			(*ps)++;
	}
	if (*ps > start)
		return (create_token(ft_strndup(start, *ps - start)));
	else
		return (NULL);
}

//RETURNS THE NEXT TOKEN FOUND IN THE STRING
t_token	*next_token(char **ps)
{
	t_token	*t;

	*ps = skip_spaces(*ps);
	if (!**ps)
		return (NULL);
	t = NULL;
	if (is_redirection_char(**ps))
		return (redirection_found(ps));
	else
		t = default_token(ps);
	return (t);
}

//READS THE COMMAND DIVIDING IT INTO TOKENS
int	lexer(t_shell	*shell, char *line)
{
	t_token	*t;
	t_token	*new;

	t = NULL;
	new = next_token(&line);
	while (new != NULL)
	{
		t = add_token(&t, new);
		new = next_token(&line);
	}
	if (!t || !syntax_check(t))
		return (-1);
	shell->tokens = t;
	return (0);
}
