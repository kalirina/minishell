/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:25:32 by enrmarti          #+#    #+#             */
/*   Updated: 2025/03/28 16:43:35 by enrmarti         ###   ########.fr       */
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
	while (i < size)
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

// 	while (*tokens)
// 	{
// 		type = is_redirection((*tokens)->str);
// 		if (!type)
// 			break;
// 		*tokens = (*tokens)->next;
// 		if (!(*tokens))
// 		{
// 			// Handle missing filename after redirection operator
// 			return (cmd);
// 		}
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

// t_command	*parse_cmd(t_token **tokens)
// {
// 	t_command	*cmd;
// 	t_token		*tmp;
// 	char		**args;
// 	int			count;

// 	tmp = *tokens;
// 	count = 0;
// 	while (tmp && ft_strncmp(tmp->str, "|", 1))
// 	{
// 		if (is_redirection(tmp->str) != NULL)
// 		{
// 			tmp = tmp->next;
// 			if (tmp == NULL)
// 			{
// 				printf("minishell : syntax error missing filename\n");
// 				return (NULL);
// 			}
// 			tmp = tmp->next;
// 		}
// 		else
// 		{
// 			count++;
// 			tmp = tmp->next;
// 		}
// 	}
// 	args = get_args(tokens, count);
// 	cmd = new_node(args);
// 	if (*tokens && is_redirection((*tokens)->str))
// 		cmd = handle_redirection(cmd, tokens);
// 	return (cmd);
// }

t_command *handle_redirection(t_command *cmd, t_token **tokens)
{
	char *type;
	t_token *next_token;

	while (*tokens)
	{
		type = is_redirection((*tokens)->str);
		if (!type)
			break;
		next_token = (*tokens)->next;
		if (next_token == NULL || is_redirection(next_token->str) != NULL
			|| (next_token && ft_strncmp(next_token->str, "|", 1) == 0))
		{
			fprintf(stderr, "minishell: syntax error near unexpected token `newline'\n");
			free_command(cmd);
			return NULL;
		}
		*tokens = (*tokens)->next;
		if (!(*tokens))
			return (cmd);
		if (ft_strncmp(type, "<", 1) == 0)
		{
			if (!add_redirection(&cmd->input, (*tokens)->str, false))
				return (free_command(cmd), NULL);
		}
		else if (ft_strncmp(type, ">>", 2) == 0)
		{
			if (!add_redirection(&cmd->output, (*tokens)->str, true))
				return (free_command(cmd), NULL);
		}
		else if (ft_strncmp(type, ">", 1) == 0)
		{
			if (!add_redirection(&cmd->output, (*tokens)->str, false))
				return (free_command(cmd), NULL);
		}
		*tokens = (*tokens)->next;
	}
	return (cmd);
}

t_command *parse_cmd(t_token **tokens)
{
	t_command	*cmd;
	t_token		*tmp;
	char 		**args;
	int			count;

	count = 0;
	tmp = *tokens;
	while (tmp && ft_strncmp(tmp->str, "|", 1) && is_redirection(tmp->str) == NULL)
	{
		if (is_redirection(tmp->str) != NULL)
			break;
		else
		{
			count++;
			tmp = tmp->next;
		}
	}
	args = get_args(tokens, count);
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
		if (ft_strncmp((*tokens)->str, "|", 1) == 0)	//AGGIUNGERE CASO PER echo figlio|cat ditroia
		{
			*tokens = (*tokens)->next;
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
	expand(shell);
	shell->cmd = parse_tokens(&shell->tokens);
	if (!shell->cmd)
		return ;
}
