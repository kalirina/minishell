/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:40:15 by enrmarti          #+#    #+#             */
/*   Updated: 2025/03/06 15:54:51 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// t_token	*new_token(char	*str)
// {
// 	t_token	*t;

// 	t = (t_token *)malloc(sizeof(t_token));
// 	if (!t)
// 		return (NULL);
// 	t->str = str;
// 	t->next = NULL;
// 	return (t);
// }

void	index_tokens(t_token *head)
{
	int	i;

	i = 0;
	if (!head)
		return ;
	while (head)
	{
		head->index = i++;
		head = head->next;
	}
}

t_token	*add_token(t_token *head, t_token *new)
{
	t_token	*tmp;

	if (!head)
		return (new);
	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->next = NULL;
	index_tokens(head);	
	return (head);
}

void	remove_node(t_token *head, int index) 
{
	t_token	*temp;
	t_token	*prev;
 
	if (!head)
		return ;
	temp = head;
	if (temp != NULL && temp->index == index)
	{
		head = temp->next;
		free(temp);
		return;
	}
	while (temp != NULL && temp->index != index)
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL)
		return;
	prev->next = temp->next;
	free(temp);
}
