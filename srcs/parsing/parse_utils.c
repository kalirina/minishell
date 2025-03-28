/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:13:27 by enrmarti          #+#    #+#             */
/*   Updated: 2025/03/28 00:31:55 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	char	*new;

	new = (char *)malloc(sizeof(char) * n + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (s[i] && i < n)
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

bool	is_space(char c)
{
	if (c && (c == ' ' || (c >= 9 && c <= 13)))
		return (true);
	return (false);
}

char	*skip_spaces(char *str)
{
	if (!str)
		return (NULL);
	while (*str && (*str == ' ' || (*str >= 9 && *str <= 13)))
		str++;
	return (str);
}

t_redirection *add_redirection(t_redirection **head, char *file, bool append)
{
	t_redirection	*new_redir;
	t_redirection	*current;

	new_redir = malloc(sizeof(t_redirection));
	if (!new_redir)
		return (NULL);
	new_redir->file = ft_strdup(file);
	new_redir->append = append;
	new_redir->next = NULL;
	if (*head == NULL)
		*head = new_redir;
	else
	{
		current = *head;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_redir;
	}
	return (new_redir);
}

void	free_redirection_list(t_redirection *head)
{
	t_redirection *current;
	t_redirection *next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free(current->file);
		free(current);
		current = next;
	}
}

void	free_command(t_command *cmd)
{
	int	i;

	if (!cmd)
		return;

    if (cmd->args)
	{
		i = 0;
		while (cmd->args[i] != NULL)
			free(cmd->args[i++]);
		free(cmd->args);
	}
	free_redirection_list(cmd->input);
	free_redirection_list(cmd->output);
	free(cmd);
}
