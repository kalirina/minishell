/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:40:15 by enrmarti          #+#    #+#             */
/*   Updated: 2025/03/11 15:46:21 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//	INDEXES ALL THE TOKENS FROM 0 TO N
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
	index_tokens(*head);	
	return (*head);
}

//	REMOVES A NODE OF THE LIST GIVEN ITS INDEX
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

//	ADDS THE STRING AT THE END OF THE GIVEN TOKEN
//	x = 0	with space				"hello"  + "world" = "hello world"
//	x = 1	no space				        ""		  = "helloworld"
// void	addstr_token(t_token *t, char *to_add, int x)
// {
// 	char	*new;
// 	int		s1;
// 	int		s2;
// 	int		i;

// 	if (!t)
// 		return;
// 	s1 = ft_strlen(t->str);
// 	s2 = ft_strlen(to_add);
// 	i = 0;
// 	if (x == 0)
// 	{
// 		new = (char *)malloc(sizeof(char) * (s1+s2) + 2);
// 		if (!new)
// 			return;
// 		while (i < s1)
// 		{
// 			new[i] = s1[i];
// 			i++;
// 		}
// 		while(i < s1+s2)
// 		{
// 			new
// 		}
// 		new[i] = '\0';
// 	}
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