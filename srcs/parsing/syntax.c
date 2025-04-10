/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:38:31 by enrmarti          #+#    #+#             */
/*   Updated: 2025/04/10 10:53:12 by enrmarti         ###   ########.fr       */
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
		printf("minishell: syntax error near unexpected token '%s'\n", t->str);
		return (false);
	}
	return (true);
}

//CHECKS IF THERE ARE CONSECUTIVES REDIRECTIONS IN THE TOKEN LIST
bool	consecutive_redirections(t_token *t)
{
	while (t->next)
	{
		if (is_redirection_char(t->str[0]) && is_redirection_char(t->next->str[0]))
		{
			printf("minishell: syntax error near unexpected token '%s'\n", t->str);
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
		printf("minishell: syntax error near unexpected token '|'\n");
		return (false);
	}
	if (!consecutive_redirections(t) || !redirection_at_end(t))
		return (false);
	return (true);
}