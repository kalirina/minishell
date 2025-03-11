/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:34:54 by enrmarti          #+#    #+#             */
/*   Updated: 2025/03/11 15:46:55 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

//RETURNS THE NEXT TOKEN FOUND IN THE STRING
t_token *next_token(char **ps)
{
	t_token		*t;
	char		*start;

	*ps = skip_spaces(*ps);
	if (!**ps)
		return (NULL);
	if (!(t = malloc(sizeof(t_token))))
		return (NULL);
	start = *ps;
	while (**ps && !is_space(**ps))
		(*ps)++;
	t->str = ft_strndup(start, *ps - start);
	t->next = NULL;
	return (t);
}

// #include <stdio.h>
//READS THE COMMAND AND DIVIDES IT IN TOKENS
void	lexer(t_shell *shell, char *line)
{
	t_token	*t;
	t_token *new;
	int	i;

	i = 0;
	t = NULL;
	new = next_token(&line);
	while (new != NULL)
	{
		t = add_token(&t, new);
		new = next_token(&line);
	}
	shell->tokens = t;
	while (t)
	{
		printf("[%d] %s\n",t->index, t->str);
		t = t->next;
	}
}
