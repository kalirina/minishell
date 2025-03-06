/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:34:54 by enrmarti          #+#    #+#             */
/*   Updated: 2025/03/06 15:59:13 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// t_node	*new_node(int type, char *value)
// {
// 	t_node *node;

// 	if (!(node = malloc(sizeof(t_node))))
// 		return (NULL);
// 	node->type = type;
// 	node->value = ft_strdup(value);
// 	node->left = NULL;
// 	node->right = NULL;
// 	return (node);
// }

// t_node	*parse_cmd(t_shell *shell, int i)
// {
// 	t_token	*t = shell->tokens[i];
// 	if (t->type != WORD)
// 		return (NULL);
// 	return (new_node(WORD, t->value));
// }

// t_node	*parse_exp(t_shell *shell, int min_precedence, int i)
// {
// 	t_node	*lhs;
// 	t_node	*rhs;
// 	t_node	*new;
// 	int		precedence;

// 	if (!(lhs = parse_cmd(shell, i)))
// 		return (NULL);
// 	while (1)
// 	{
// 		precedence = get_precedence(shell->tokens[i]->type);
// 		if (precedence < min_precedence)
// 			return (lhs);
// 		i++;
// 		rhs = parse_exp(shell, precedence + 1, i);
// 		new = new_node(shell->tokens[i]->type, tokens[i]->value);
// 		new->left = lhs;
// 		new->right = rhs;

// 		lhs = new;
// 	}
// }

int	find_type(char *pt)
{
	if (!pt)
		return (0);
	if (ft_strncmp(pt, "|", 1) == 0)
		return (3);
	if (ft_strncmp(pt, "<", 1) == 0)
		return (4);
	if (ft_strncmp(pt, ">", 2) == 0)
		return (5);
	if (ft_strncmp(pt, ">>", 2) == 0)
		return (6);
	if (ft_strncmp(pt, "<<", 2) == 0)
		return (7);
	if (ft_strncmp(pt, ";", 1) == 0)
		return (8);
	else
		return (1);
}

t_token *next_token(char **ps)
{
	t_token		*t;
	char		*start;

	*ps = skip_spaces(*ps);
	if (!**ps)
		return (NULL);
	if (!(t = malloc(sizeof(t_token))))
		return (NULL);
	start = *ps;
	while (**ps && !is_space(**ps))
		(*ps)++;
	t->str = ft_strndup(start, *ps - start);
	if (**ps)
	{
		**ps = '\0';
		(*ps)++;
	}
	return (t);
}

void	lexer(t_shell *shell, char *line)
{
	t_token	*t;
	int	i;

	i = 0;
	t = next_token(&line);
	while (t != NULL)
	{
		*shell->tokens = add_token(*shell->tokens, t);
		t = next_token(&line);
	}
	
	t = *shell->tokens;
	while (t)
	{
		printf("[%d] str: %s", t->index, t->str);
		t = t->next;
	}
		
}
