/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:40:15 by enrmarti          #+#    #+#             */
/*   Updated: 2025/03/27 11:09:14 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


//	ADDS A TOKEN AT THE END OF THE LIST
t_token	*add_token(t_token **head, t_token *new)
{
	t_token	*tmp;

	if (!head || !(*head))
		return (new);
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->next = NULL;
	return (*head);
}

// //	REMOVES A NODE OF THE LIST GIVEN ITS INDEX
// void	remove_node(t_token *head, int index)
// {
// 	t_token	*temp;
// 	t_token	*prev;

// 	if (!head)
// 		return ;
// 	temp = head;
// 	if (temp != NULL && temp->index == index)
// 	{
// 		head = temp->next;
// 		free(temp);
// 		return;
// 	}
// 	while (temp != NULL && temp->index != index)
// 	{
// 		prev = temp;
// 		temp = temp->next;
// 	}
// 	if (temp == NULL)
// 		return;
// 	prev->next = temp->next;
// 	free(temp);
// }

// //	ADDS THE STRING AT THE END OF THE GIVEN TOKEN
// void	addstr_token(t_token *t, char *to_add)
// {
// 	char	*new;
// 	int		s1;
// 	int		s2;
// 	int		i;
// 	int		j;

// 	if (!t)
// 		return;
// 	s1 = ft_strlen(t->str);
// 	s2 = ft_strlen(to_add);
// 	i = 0;
// 	new = (char *)malloc(sizeof(char) * (s1+s2) + 1);
// 	if (!new)
// 		return;
// 	while (i < s1)
// 	{
// 		new[i] = s1[i];
// 		i++;
// 	}
// 	j = 0;
// 	while(i < s1+s2)
// 		new[i++] = s2[j++];
// 	new[i] = '\0';
// 	free(t->str);
// 	t->str = new;
// }

//	FREES THE LIST OF TOKENS
void	free_tokens(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->str);
		free(tmp);
	}
}
