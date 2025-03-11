/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:25:32 by enrmarti          #+#    #+#             */
/*   Updated: 2025/03/11 16:33:30 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


t_node	*new_node(int type, char **args, t_node *left, t_node *right)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	new->type = type;
	new->args = args;
	new->left = left;
	new->right = right;
	return (new);
}

t_node	*new_redirect_node(char *operator, char **filename, t_node *left, t_node *right)
{
	t_node	*new;
	int		type;

	new = malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	if (ft_strncmp(operator, "<", 1) == 0)
		type = INPUT;
	else if (ft_strncmp(operator, ">", 1) == 0)
		type = OUTPUT;
	else if (ft_strncmp(operator, "<<", 2) == 0)
		type = HEREDOC;
	else if (ft_strncmp(operator, ">>", 2) == 0)
		type = APPEND;
	else
		type = 0;
	new->type = type;
	new->args = filename;
	new->left = left;
	new->right = right;
	return (new);
}

t_node	*parse_cmd(t_token **tokens)
{
	t_token 	*tmp;
	char		**args;
	int			count;
	int			i;

	tmp = *tokens;
	count = 0;
	while (tmp && !ft_strncmp(tmp->str, "|", 1) && !ft_strncmp(tmp->str, ">", 1)
			&& !ft_strncmp(tmp->str, "<", 1) && !ft_strncmp(tmp->str, "<<", 2)
			&& !ft_strncmp(tmp->str, ">>", 2))
	{
		count++;
		tmp = tmp->next;
	}
	if (count == 0)
		return (NULL);
	args = malloc((count + 1) * sizeof(char *));
	if (!args)
		return (NULL);
	i = 0;
	while (i < count)
	{
		args[i++] = (*tokens)->str;
		*tokens = (*tokens)->next;
	}
	args[count] = NULL;
	return (new_node(CMD, args, NULL, NULL));
}

t_node	*parse_pipe(t_token **tokens)
{
	t_node *left;
	t_node *right;
	
	left = parse_cmd(tokens);
	while (*tokens && ft_strncmp((*tokens)->str, "|", 1) == 0)
	{
		*tokens = (*tokens)->next;
		right = parse_cmd(tokens);
		left = new_node(PIPE, NULL, left, right);
	}
	return (left);
}

t_node	*parse_redirect(t_token **tokens)
{
	t_node	*left;
	char	*operator;
	char	**filename;

	left = parse_pipe(tokens);
	while (*tokens && (!ft_strncmp((*tokens)->str, ">", 1) || !ft_strncmp((*tokens)->str, "<", 1)
			|| !ft_strncmp((*tokens)->str, ">>", 2) || !ft_strncmp((*tokens)->str, "<<", 2)))
	{
		operator = (*tokens)->str;
		(*tokens) = (*tokens)->next;
		if (!*tokens)
			return (left);
		filename = malloc(2 * sizeof(char *));
		filename[0] = (*tokens)->str;
		filename[1] = NULL;		
		*tokens = (*tokens)->next;
		left = new_redirect_node(operator, filename, left, NULL);
	}
	return (left);
}

void print_ast(t_node *node, int depth) {
    if (!node) return;
    for (int i = 0; i < depth; i++) printf("  ");

    if (node->type == CMD) {
        printf("COMMAND: ");
        for (int i = 0; node->args[i]; i++)
            printf("%s ", node->args[i]);
        printf("\n");
    } else if (node->type == PIPE) {
        printf("PIPE\n");
    } else if ((node->type == INPUT) || (node->type == OUTPUT)
	|| (node->type == APPEND) || (node->type == HEREDOC)) {
        printf("REDIRECTION (%s)\n", node->args[0]);
    }

    print_ast(node->left, depth + 1);
    print_ast(node->right, depth + 1);
}

void	parser(t_shell *shell)
{
	if (!shell->tokens)
		return ;
	shell->ast = parse_redirect(&shell->tokens);
	if (!shell->ast)
		return ;
	print_ast(shell->ast, 1);
}