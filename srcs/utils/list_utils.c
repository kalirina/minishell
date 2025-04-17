/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:40:15 by enrmarti          #+#    #+#             */
/*   Updated: 2025/04/09 23:22:36 by irkalini         ###   ########.fr       */
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

t_command	*new_node(void)
{
	t_command	*new;

	new = malloc(sizeof(t_command));
	if (!new)
		return (NULL);
	new->args = NULL;
	new->input = NULL;
	new->output = NULL;
	new->next = NULL;
	return (new);
}

char	*is_redirection(char *str)
{
	if (ft_strncmp(str, ">>", 2) == 0)
		return (">>");
	if (ft_strncmp(str, ">", 1) == 0)
		return (">");
	if (ft_strncmp(str, "<<", 2) == 0)
		return ("<<");
	if (ft_strncmp(str, "<", 1) == 0)
		return ("<");
	return (NULL);
}

int	count_commands(t_command *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
} 
 
void	free_split(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
