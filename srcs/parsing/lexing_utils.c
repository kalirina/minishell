/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:45:01 by enrmarti          #+#    #+#             */
/*   Updated: 2025/04/12 20:45:52 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*process_quotes(char *quoted_str, char *final_str, int *i, int len, bool *in_squotes, bool *in_dquotes)
{
	char	c;

	while (*i < len)
	{
		c = quoted_str[*i];
		if (c == '\'' && !*in_dquotes)
		{
			*in_squotes = !*in_squotes;
			(*i)++;
		}
		else if (c == '"' && !*in_squotes)
		{
			*in_dquotes = !*in_dquotes;
			(*i)++;
		}
		else
		{
			final_str = append_char(final_str, c);
			(*i)++;
		}
	}
	return (final_str);
}

void	perform_quote_removal(t_shell *shell)
{
	t_token	*current;
	char	*quoted_str;
	char	*final_str;
	int		i;
	int		len;
	bool	in_squotes;
	bool	in_dquotes;

	current = shell->tokens;
	while (current)
	{
		quoted_str = current->str;
		if (quoted_str)
		{
			final_str = ft_strdup("");
			i = 0;
			len = ft_strlen(quoted_str);
			in_squotes = false;
			in_dquotes = false;
			final_str = process_quotes(quoted_str, final_str, &i, len, &in_squotes, &in_dquotes);
			free(quoted_str);
			current->str = final_str;
		}
		current = current->next;
	}
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
