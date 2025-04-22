/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:13:27 by enrmarti          #+#    #+#             */
/*   Updated: 2025/04/22 12:33:53 by enrmarti         ###   ########.fr       */
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

t_redirection	*add_redirection(t_redirection **head, char *file,
				bool append, bool heredoc)
{
	t_redirection	*new_redir;
	t_redirection	*current;

	new_redir = malloc(sizeof(t_redirection));
	if (!new_redir)
		return (NULL);
	new_redir->file = ft_strdup(file);
	new_redir->append = append;
	new_redir->heredoc = heredoc;
	new_redir->fd_heredoc = -1;
	new_redir->next = NULL;
	if (*head == NULL)
		*head = new_redir;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_redir;
	}
	return (new_redir);
}

void	cleanup_command_line(t_shell *shell)
{
	free_command(shell->cmd);
	shell->cmd = NULL;
}
