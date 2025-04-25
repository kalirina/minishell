/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:38:31 by enrmarti          #+#    #+#             */
/*   Updated: 2025/04/25 16:12:28 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//CHECKS IF THE LAST TOKEN IS A REDIRECTION
// ex.   grep test <input >
bool	redirection_at_end(t_token *t, t_shell *shell)
{
	while (t->next)
		t = t->next;
	if (is_redirection_char(t->str[0]))
	{
		printf(RED "minishell: syntax error near unexpected token '%s'\n" RES,
			t->str);
		shell->exit_status = 2;
		return (false);
	}
	return (true);
}

//CHECKS FOR CONSECUTIVE REDIRECTIONS BUT IGNORES | >
bool	consecutive_redirections(t_token *t, t_shell *shell)
{
	bool	current_is_redir;
	bool	next_is_redir;

	while (t && t->next)
	{
		current_is_redir = is_redirection_char(t->str[0]);
		next_is_redir = is_redirection_char(t->next->str[0]);
		if (current_is_redir && next_is_redir
			&& !(t->str[0] == '|' && (t->next->str[0] == '<'
					|| t->next->str[0] == '>')))
		{
			printf(RED "minishell: syntax error "
				"near unexpected token '%s'\n" RES, t->next->str);
			shell->exit_status = 2;
			return (false);
		}
		t = t->next;
	}
	return (true);
}

//PERFORMS CHECKS ON THE SYNTAX OF THE TOKEN LIST
bool	syntax_check(t_token *t, t_shell *shell)
{
	if (!t)
		return (false);
	if (ft_strncmp(t->str, "|", 1) == 0)
	{
		printf(RED "minishell: syntax error near unexpected token '|'\n" RES);
		shell->exit_status = 2;
		return (false);
	}
	if (!consecutive_redirections(t, shell) || !redirection_at_end(t, shell))
		return (false);
	return (true);
}

//SKIPS QUOTES WHILE KEEPING TRACK
bool	check_quotes_inquotes(t_expansion *exp)
{
	char	*token;
	int		i;

	i = exp->i;
	if (i >= exp->len)
		return (false);
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
	char	next;
	int		i;

	i = exp->i;
	if (i >= exp->len)
		return (false);
	token = exp->token;
	next = token[i + 1];
	if (next && token[i] == '\'' && next == '\'')
	{
		exp->i += 2;
		return (true);
	}
	else if (next && token[i] == '"' && next == '"')
	{
		exp->i += 2;
		return (true);
	}
	return (false);
}
