/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:25:32 by enrmarti          #+#    #+#             */
/*   Updated: 2025/04/23 13:15:06 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**get_args(t_token **tokens, int size)
{
	char	**args;
	int		i;

	if (size == 0)
	{
		args = malloc((2) * sizeof(char *));
		args[0] = ft_strdup(" ");
		args[1] = NULL;
		return (args);
	}
	args = malloc((size + 1) * sizeof(char *));
	if (!args)
		return (NULL);
	i = 0;
	while (i < size && *tokens)
	{
		args[i++] = ft_strdup((*tokens)->str);
		*tokens = (*tokens)->next;
	}
	args[size] = NULL;
	return (args);
}

t_command	*handle_redirection(t_command *cmd, t_token **tokens, char *type)
{
	if (ft_strncmp(type, "<<", 2) == 0)
	{
		if (!add_redirection(&cmd->input, (*tokens)->next->str, false, true))
			return (free_command(cmd), NULL);
		*tokens = (*tokens)->next;
	}
	else if (ft_strncmp(type, "<", 1) == 0)
	{
		if (!add_redirection(&cmd->input, (*tokens)->next->str, false, false))
			return (free_command(cmd), NULL);
		*tokens = (*tokens)->next;
	}
	else if (ft_strncmp(type, ">>", 2) == 0)
	{
		if (!add_redirection(&cmd->output, (*tokens)->next->str, true, false))
			return (free_command(cmd), NULL);
		*tokens = (*tokens)->next;
	}
	else if (ft_strncmp(type, ">", 1) == 0)
	{
		if (!add_redirection(&cmd->output, (*tokens)->next->str, false, false))
			return (free_command(cmd), NULL);
		*tokens = (*tokens)->next;
	}
	return (cmd);
}

t_command	*parse_cmd(t_token **tokens)
{
	t_command	*cmd;
	t_token		*tmp;
	int			count;

	count = 0;
	cmd = new_node();
	while (*tokens && is_redirection((*tokens)->str))
	{
		cmd = handle_redirection(cmd, tokens, is_redirection((*tokens)->str));
		*tokens = (*tokens)->next;
	}
	tmp = *tokens;
	while (tmp && ft_strncmp(tmp->str, "|", 1)
		&& is_redirection(tmp->str) == NULL)
	{
		count++;
		tmp = tmp->next;
	}
	cmd->args = get_args(tokens, count);
	while (*tokens && is_redirection((*tokens)->str))
	{
		cmd = handle_redirection(cmd, tokens, is_redirection((*tokens)->str));
		*tokens = (*tokens)->next;
	}
	return (cmd);
}

t_command	*parse_tokens(t_token **tokens)
{
	t_command	*first;
	t_command	*current;

	first = parse_cmd(tokens);
	current = first;
	while (*tokens)
	{
		if (ft_strncmp((*tokens)->str, "|", 1) == 0)
		{
			*tokens = (*tokens)->next;
			if (!first || !(*tokens) || ft_strncmp((*tokens)->str, "|", 1) == 0)
				return (printf(RED "minishell: syntax error "
						"near unexpected token '|'\n" RES), NULL);
			current->next = parse_cmd(tokens);
			current = current->next;
		}
		else
			break ;
	}
	return (first);
}

int	parser(t_shell *shell)
{
	t_token	*head;

	if (!shell->tokens)
		return (-1);
	head = shell->tokens;
	if (expand(shell) == 0)
	{
		perform_quote_removal(shell);
		shell->cmd = parse_tokens(&shell->tokens);
	}
	free_tokens(head, shell);
	return (0);
}
