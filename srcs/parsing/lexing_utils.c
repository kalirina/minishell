/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:45:01 by enrmarti          #+#    #+#             */
/*   Updated: 2025/04/22 17:06:02 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

typedef struct s_quoteremoval
{
	char	*res;
	char	*orig;
	int		i;
	bool	in_squotes;
	bool	in_dquotes;
}	t_removal;

t_removal	*init_rem(char *orig)
{
	t_removal	*t;

	t = malloc(sizeof(t_removal));
	if (!t)
		return (NULL);
	t->orig = orig;
	t->i = 0;
	t->res = ft_strdup("");
	t->in_dquotes = false;
	t->in_squotes = false;
	return (t);
}

t_token	*create_token(char *str)
{
	t_token	*t;

	if (!str)
		return (NULL);
	t = malloc(sizeof(t_token));
	if (!t)
	{
		free(str);
		return (NULL);
	}
	t->str = str;
	t->next = NULL;
	return (t);
}

void	process_quotes(t_removal *rem)
{
	char	c;
	int		len;

	len = ft_strlen(rem->orig);
	while (rem->i < len)
	{
		c = rem->orig[rem->i];
		if (c == '\'' && !rem->in_dquotes)
		{
			rem->in_squotes = !rem->in_squotes;
			rem->i++;
		}
		else if (c == '"' && !rem->in_squotes)
		{
			rem->in_dquotes = !rem->in_dquotes;
			rem->i++;
		}
		else
		{
			rem->res = append_char(rem->res, c);
			rem->i++;
		}
	}
}

void	perform_quote_removal(t_shell *shell)
{
	t_token		*current;
	t_removal	*rem;

	current = shell->tokens;
	while (current)
	{
		if (current->str)
		{
			rem = init_rem(current->str);
			process_quotes(rem);
			current->str = rem->res;
			free(rem->orig);
			free(rem);
		}
		current = current->next;
	}
}
