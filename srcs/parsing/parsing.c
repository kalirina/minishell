/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:25:32 by enrmarti          #+#    #+#             */
/*   Updated: 2025/03/24 19:19:20 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


t_command	*new_node(int type, char **args, char *input, char *output, bool append)
{
	t_command	*new;

	new = malloc(sizeof(t_command));
	if (!new)
		return (NULL);
	new->type = type;
	new->args = args;
	new->input = input;
	new->output = output;
	new->append = append;
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

t_command	*handle_redirection(t_token	**tokens, char **args)
{
	char	*type;
	char	*input;
	char	*output;
	bool	append;

	append = false;
	input = NULL;
	output = NULL;
	while (*tokens && ft_strncmp((*tokens)->str, "|", 1))
	{
		type = is_redirection((*tokens)->str);
		if (!type)
			break;
		*tokens = (*tokens)->next;
		if (!(*tokens))
			break;
		if (ft_strncmp(type, "<", 1) == 0)
			input = (*tokens)->str;
		else if (ft_strncmp(type, ">>", 2) == 0)
		{
			append = true;
			printf("\n!!\n");
			output = (*tokens)->str;
		}
		else if (ft_strncmp(type, ">", 1) == 0)
			output = (*tokens)->str;
		*tokens = (*tokens)->next;
	}
	return(new_node(CMD, args, input, output, append));
}


t_command	*parse_cmd(t_token **tokens)
{
	t_token		*tmp;
	char		**args;
	char		*redir;
	int			count;

	tmp = *tokens;
	redir = NULL;
	count = 0;
	while (tmp && ft_strncmp(tmp->str, "|", 1))
	{
		redir = is_redirection(tmp->str);
		if (redir != NULL)
			break;
		count++;
		tmp = tmp->next;
	}
	if (count == 0)
		return (NULL);
	if (redir == NULL)
	{
		args = get_args(tokens, count);
		return (new_node(CMD, args, NULL, NULL, false));
	}
	args = get_args(tokens, count);
	return (handle_redirection(tokens, args));
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
			current->next = parse_cmd(tokens);
			current = current->next;
		}
		else
			break;
	}
	return (first);
}

// void	print_cmd(t_command *cmd)
// {
// 	printf("COMMAND\n type: %d \n input : %s - output : %s \n", cmd->type, cmd->input, cmd->output);
// 	int i = 0;
// 	printf("args: \n");
// 	while (cmd->args[i])
// 	{
// 		printf("[%d]\t%s\n", i, cmd->args[i]);
// 		i++;
// 	}
// 	printf("append: %d\n", cmd->append);
// }


void	parser(t_shell *shell)
{
	if (!shell->tokens)
		return ;
	shell->cmd = parse_tokens(&shell->tokens);
	if (!shell->cmd)
		return ;
//	print_cmd(shell->cmd);
//	if (shell->cmd->next)
//		print_cmd(shell->cmd->next);
}
