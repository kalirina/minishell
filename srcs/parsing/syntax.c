/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:38:31 by enrmarti          #+#    #+#             */
/*   Updated: 2025/04/22 16:43:10 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//CHECKS IF THE LAST TOKEN IS A REDIRECTION
// ex.   grep test <input >
bool	redirection_at_end(t_token *t)
{
	while (t->next)
		t = t->next;
	if (is_redirection_char(t->str[0]))
	{
		printf(RED "minishell: syntax error near unexpected token '%s'\n" RES,
			t->str);
		return (false);
	}
	return (true);
}

//CHECKS IF THERE ARE CONSECUTIVES REDIRECTIONS IN THE TOKEN LIST
bool	consecutive_redirections(t_token *t)
{
	while (t->next)
	{
		if (is_redirection_char(t->str[0])
			&& is_redirection_char(t->next->str[0]))
		{
			printf(RED "minishell: syntax error "
			"near unexpected token '%s'\n" RES, t->str);
			return (false);
		}
		t = t->next;
	}
	return (true);
}

//PERFORMS CHECKS ON THE SYNTAX OF THE TOKEN LIST
bool	syntax_check(t_token *t)
{
	if (!t)
		return (false);
	if (ft_strncmp(t->str, "|", 1) == 0)
	{
		printf(RED "minishell: syntax error near unexpected token '|'\n" RES);
		return (false);
	}
	if (!consecutive_redirections(t) || !redirection_at_end(t))
		return (false);
	return (true);
}

//SKIPS QUOTES WHILE KEEPING TRACK
bool	check_quotes_inquotes(t_expansion *exp)
{
	char	*token;
	int		i;

	i = exp->i;
	token = exp->token;
	if (token[i] == '\'' && exp->in_single_quote)
	{
		exp->res = append_char(exp->res, '$');
		exp->i++;
		exp->in_single_quote = !exp->in_single_quote;
		return (true);
	}
	else if (token[i] == '"' && exp->in_double_quote)
	{
		exp->res = append_char(exp->res, '$');
		exp->i++;
		exp->in_double_quote = !exp->in_double_quote;
		return (true);
	}
	return (false);
}

//HANDLES (SKIPS) THE $'' AND $"" VARS
bool	check_dollar_quotes(t_expansion *exp)
{
	char	*token;
	int		i;

	i = exp->i;
	token = exp->token;
	if (token[i + 1] && token[i] == '\'' && token[i + 1] == '\'')
	{
		exp->i += 2;
		return (true);
	}
	else if (token[i + 1] && token[i] == '"' && token[i + 1] == '"')
	{
		exp->i += 2;
		return (true);
	}
	return (false);
}
