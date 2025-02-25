/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:34:54 by enrmarti          #+#    #+#             */
/*   Updated: 2025/02/25 18:30:12 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//DOESNT CHECK FOR ARGS, IT CAN BE CHECKED AFTER BY LOOKING AT THE TOKENS IN ORDER
int	find_type(char *pt)
{
	if (!pt)
		return (0);
	if (*pt == '-' && pt[1])
		return (2);
	if (ft_strcmp(pt, "|") == 0)
		return (4);
	if (ft_strcmp(pt, "<") == 0)
		return (5);
	if (ft_strcmp(pt, ">") == 0)
		return (6);
	if (ft_strcmp(pt, ">>") == 0)
		return (7);
	if (ft_strcmp(pt, "<<") == 0)
		return (8);
	if (ft_strcmp(pt, ";") == 0)
		return (9);
	else
		return (1);
}

t_token *next_token(char **ps)
{
	t_token		*t;
	static int	i;
	
	if (!(t = mallo(sizeof(t_token))))
		return (NULL);
	*ps = skip_spaces(*ps);
	if (!**ps)
	{
		free(t);
		return (NULL);
	}
	t->str = *ps;
	while (**ps && !is_space(**ps))
		(*ps)++;
	if (**ps)
	{
		**ps = '\0';
		(*ps)++;
	}
	t->type = find_type(t->str);
	t->index = i++;
	t->prev = NULL;
	t->next = NULL;
	return (t);
}

t_token	*parsing(char *buff)
{
	t_token	*head;
	t_token	*tail;
	char	*ps;

	ps = buff;
	while (*ps)
	{
		t_token *new_token = next_token(&ps);
		if (!new_token)
			break;

		if (!head)
		{
			head = new_token;
			tail = new_token;
		}
		else
		{
		tail->next = new_token;
			new_token->prev = tail;
			tail = new_token;
		}
	}	
	return (head);
}