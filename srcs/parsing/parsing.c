/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:25:32 by enrmarti          #+#    #+#             */
/*   Updated: 2025/04/10 14:17:29 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_command	*new_node(char **args)
{
	t_command	*new;

	new = malloc(sizeof(t_command));
	if (!new)
		return (NULL);
	new->args = args;
	new->input = NULL;
	new->output = NULL;
	new->next = NULL;
	return (new);
}

char	**get_args(t_token **tokens, int size)
{
	char	**args;
	int		i = 0;

	args = malloc((size + 1) * sizeof(char *));
	if (!args)
		return (NULL);
	while (i < size && *tokens)
	{
		args[i++] = (*tokens)->str;
		*tokens = (*tokens)->next;
	}
	args[size] = NULL;
	return (args);
}

char		*is_redirection(char *str)
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


// t_command *handle_redirection(t_command *cmd, t_token **tokens)
// {
// 	char *type;
// 	t_token *next_token;

// 	while (*tokens)
// 	{
// 		type = is_redirection((*tokens)->str);
// 		if (!type)
// 			break;
// 		next_token = (*tokens)->next;
// 		if (next_token == NULL || is_redirection(next_token->str) != NULL
// 			|| (next_token && ft_strncmp(next_token->str, "|", 1) == 0))
// 		{
// 			fprintf(stderr, "minishell: syntax error near unexpected token `newline'\n");
// 			free_command(cmd);
// 			return NULL;
// 		}
// 		*tokens = (*tokens)->next;
// 		if (!(*tokens))
// 			return (cmd);
// 		if (ft_strncmp(type, "<", 1) == 0)
// 		{
// 			if (!add_redirection(&cmd->input, (*tokens)->str, false))
// 				return (free_command(cmd), NULL);
// 		}
// 		else if (ft_strncmp(type, ">>", 2) == 0)
// 		{
// 			if (!add_redirection(&cmd->output, (*tokens)->str, true))
// 				return (free_command(cmd), NULL);
// 		}
// 		else if (ft_strncmp(type, ">", 1) == 0)
// 		{
// 			if (!add_redirection(&cmd->output, (*tokens)->str, false))
// 				return (free_command(cmd), NULL);
// 		}
// 		*tokens = (*tokens)->next;
// 	}
// 	return (cmd);
// }

t_command *handle_redirection(t_command *cmd, t_token **tokens)
{
	char		*type;
	t_token		*next_token;

	
	while (*tokens)
	{
		type = is_redirection((*tokens)->str);
		if (!type)
			break;
		next_token = (*tokens)->next;
		if (next_token == NULL)
		{
			printf("minishell: syntax error near unexpected token `%s'\n", (*tokens)->str);
			return (free_command(cmd), NULL);
		}
		else if (ft_strncmp(type, "<<", 2) == 0)
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
		*tokens = (*tokens)->next;
	}
	return (cmd);
}

t_command *parse_cmd(t_token **tokens)
{
	t_command	*cmd;
	t_token		*tmp;
	char		**args;
	int			count;

	count = 0;
	tmp = *tokens;
	while (tmp && ft_strncmp(tmp->str, "|", 1) && is_redirection(tmp->str) == NULL)
	{
		count++;
		tmp = tmp->next;
	}
	args = get_args(tokens, count);
	if (args)
		cmd = new_node(args);
	if (*tokens && is_redirection((*tokens)->str))
		cmd = handle_redirection(cmd, tokens);
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
				return (printf("minishell: syntax error near unexpected token '|'\n"), NULL);
			current->next = parse_cmd(tokens);
			current = current->next;
		}
		else
			break;
	}
	return (first);
}

void	parser(t_shell *shell)
{
	if (!shell->tokens)
		return ;
	if (expand(shell) == 0)
		shell->cmd = parse_tokens(&shell->tokens);
	if (!shell->cmd)
		return ;
}
