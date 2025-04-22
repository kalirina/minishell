/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:40:15 by enrmarti          #+#    #+#             */
/*   Updated: 2025/04/22 18:03:22 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//	ADDS A TOKEN AT THE END OF THE LIST
t_token	*add_token(t_token **head, t_token *new)
{
	t_token	*tmp;

	if (!head || !new)
		return (NULL);
	if (!*head)
	{
		*head = new;
		new->next = NULL;
		return (*head);
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->next = NULL;
	return (*head);
}

//	FREES THE LIST OF TOKENS
void	free_tokens(t_token *head, t_shell *shell)
{
	t_token	*tmp;

	if (!head)
		return ;
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->str);
		free(tmp);
	}
	shell->tokens = NULL;
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
