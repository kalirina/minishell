/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:34:54 by enrmarti          #+#    #+#             */
/*   Updated: 2025/02/27 18:23:20 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	find_type(char *pt)
{
	if (!pt)
		return (0);
	if (*pt == '$')
		return (2);
	if (ft_strcmp(pt, "|") == 0)
		return (3);
	if (ft_strcmp(pt, "<") == 0)
		return (4);
	if (ft_strcmp(pt, ">") == 0)
		return (5);
	if (ft_strcmp(pt, ">>") == 0)
		return (6);
	if (ft_strcmp(pt, "<<") == 0)
		return (7);
	if (ft_strcmp(pt, ";") == 0)
		return (8);
	else
		return (1);
}

t_token *next_token(char **ps)
{
	t_token		*t;
	char		*start;
	
	if (!(t = malloc(sizeof(t_token))))
		return (NULL);
	*ps = skip_spaces(*ps);
	if (!**ps)
	{
		free(t);
		return (NULL);
	}
	start = *ps;
	while (**ps && !is_space(**ps)) 
		(*ps)++;
	t->value = ft_strndup(start, *ps - start);
	t->type = find_type(t->str);
	if (**ps)
	{
		**ps = '\0';
		(*ps)++;
	}
	return (t);
}

void	process_input(t_shell *shell, char *ps)
{
	int		i;
	
	i = 0;
	while (1)
	{
		shell.tokens[i] = next_token(&ps);
		if (shell->tokens[i] == NULL)
			break;
		i++;
	}
	
}

t_node	*new_node(int type, char *value)
{
	t_node *node;
	
	if (!(node = malloc(sizeof(t_node))))
		return (NULL);
	node->type = type;
	node->value = ft_strdup(value);
	node->left = NULL;
	node->right = NULL;
	return (node);	
}

t_node	*parse_cmd(t_shell *shell, int i)
{
	t_token	*t = shell->tonkens[i];
	if (t->type != WORD)
		return (NULL);
	return (new_node(WORD, t->value));
}

t_node	*parse_exp(t_shell *shell, int min_precedence, int i)
{
	t_node	*lhs;
	t_node	*rhs;
	t_node	*new;
	int		precedence;

	if (!(lhs = parse_cmd(shell, i)))
		return (NULL);
	while (1)
	{
		precedence = get_precedence(shell->tokens[i]->type);
		if (precedence < min_precedence)
			return (lhs);
		i++;
		rhs = parse_exp(shell, precedence + 1, i);
		new = new_node(shell->tokens[i]->type, tokens[i]->value);
		new->left = lhs;
		new->right = rhs;
		
		lhs = new;
	}
}