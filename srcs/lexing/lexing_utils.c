/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:45:01 by enrmarti          #+#    #+#             */
/*   Updated: 2025/03/27 23:41:01 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*remove_delimiter_quotes(t_token *tokens, int len)
{
	char	*res;
	int		i;

	i = 0;
	res = malloc(sizeof(char) * len - 1);
	if (!res)
		return (NULL);
	while (i < len - 2)
	{
		res[i] = tokens->str[i + 1];
		i++;
	}
	res[i] = '\0';
	free(tokens->str);
	return (res);
}

char	*remove_extra_quotes(t_token *tokens, int len)
{
	char 	*res;
	int		i;
	int		j;
	int		in_quote;
	char	quote_type;

	in_quote = 0;
	quote_type = 0;
	res = (char *)malloc(len + 1);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (tokens->str[i])
	{
		if (tokens->str[i] == '\'' || tokens->str[i] == '"')
		{
			if (in_quote && tokens->str[i] == quote_type)
			{
				in_quote = 0;
				quote_type = 0;
			}
			else if (!in_quote)
			{
				in_quote = 1;
				quote_type = tokens->str[i];
			}
		}
		else
		{
			res[j++] = tokens->str[i];
		}
		i++;
	}
	res[j] = '\0';
	free(tokens->str);
	return (res);
}

t_token	*clean_tokens(t_token *tokens)
{
	t_token	*start;
	int		len;

	if (!tokens)
		return (NULL);
	start = tokens;
	while (tokens)
	{
		len = ft_strlen(tokens->str);
		if (((tokens->str[0] == '\'' && tokens->str[len - 1]  == '\'')
			|| (tokens->str[0] == '"' && tokens->str[len - 1]  == '"'))
			&& len > 2)
		{
			tokens->quotes = tokens->str[0];
			tokens->str = remove_delimiter_quotes(tokens, len);
		}
		else
			tokens->str = remove_extra_quotes(tokens, len);
		tokens = tokens->next;
	}
	return (start);
}


t_token	*create_token(char *str)
{
	t_token *t;

	t = malloc(sizeof(t_token));
	if (!t)
		return (NULL);
	t->str = str;
	t->next = NULL;
	t->quotes = 0;
	return (t);
}
