/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:20:15 by enrmarti          #+#    #+#             */
/*   Updated: 2025/04/23 15:49:38 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//KEEPS TRACK WHETHER WE ARE INSIDE OF QUOTES OR NOT
void	handle_quotes(t_expansion *exp)
{
	exp->res = append_char(exp->res, exp->token[exp->i]);
	if (exp->token[exp->i] == '\'')
	{
		if (!exp->in_double_quote)
			exp->in_single_quote = !(exp->in_single_quote);
	}
	else if (exp->token[exp->i] == '"')
	{
		if (!exp->in_single_quote)
			exp->in_double_quote = !(exp->in_double_quote);
	}
	exp->i++;
}

//HANDLES STANDARD ENV VARS, $HOME $dontexist etc
void	default_var(t_shell *shell, t_expansion *exp)
{
	char	*var_name;
	char	*value;
	int		start_index;
	int		len;

	value = NULL;
	start_index = exp->i;
	while (exp->token[exp->i] && (ft_isalnum(exp->token[exp->i])
			|| exp->token[exp->i] == '_'))
		exp->i++;
	len = exp->i - start_index;
	var_name = ft_substr(&exp->token[start_index], 0, len);
	if (ft_strncmp(var_name, "UID", 3) == 0 && ft_strlen(var_name) == 3)
		value = ft_itoa(shell->uid);
	else
		value = echo_env_val(shell, var_name);
	free(var_name);
	if (value)
	{
		exp->res = new_strjoin(exp->res, value);
		free(value);
	}
}

//HANDLES CASES SUCH AS $$, $?, $=, etc
void	handle_var_expansion(t_shell *shell, t_expansion *exp)
{
	pid_t	pid;
	char	*value;

	if (exp->token[exp->i] == '?')
	{
		value = ft_itoa(shell->exit_status);
		exp->res = new_strjoin(exp->res, value);
		free(value);
		exp->i++;
	}
	else if (exp->token[exp->i] == '\0' || exp->token[exp->i] == '='
		|| exp->token[exp->i] == ':' || exp->token[exp->i] == ' ')
		exp->res = append_char(exp->res, '$');
	else if (ft_isdigit(exp->token[exp->i]))
		exp->i++;
	else if (exp->token[exp->i] == '$')
	{
		pid = getpid();
		value = ft_itoa(pid);
		exp->res = new_strjoin(exp->res, value);
		exp->i++;
		free(value);
	}
	else
		default_var(shell, exp);
}

//EXPANDS THE ENV VARS FOUND IN THE STRING INSIDE THE EXP STRUCTURE
char	*expand_str(t_shell *shell, t_expansion *exp)
{
	while (exp->i < exp->len)
	{
		if (exp->token[exp->i] == '\'' || exp->token[exp->i] == '"')
			handle_quotes(exp);
		else if (exp->token[exp->i] == '\\')
		{
			if (!(exp->token[exp->i + 1]))
				return (exp->res);
			exp->res = append_char(exp->res, exp->token[exp->i + 1]);
			exp->i += 2;
		}
		else if (exp->token[exp->i] == '$' && !(exp->in_single_quote))
		{
			exp->i++;
			if (!check_quotes_inquotes(exp) && !check_dollar_quotes(exp))
				handle_var_expansion(shell, exp);
		}
		else
		{
			exp->res = append_char(exp->res, exp->token[exp->i]);
			exp->i++;
		}
	}
	return (exp->res);
}

//GOES THROUGH EVERY NODE OF THE TOKEN LIST EXPANDING ITS VALUE
int	expand(t_shell *shell)
{
	t_token			*current;
	t_expansion		*exp;
	char			*original_str;

	current = shell->tokens;
	if (!current)
		return (-1);
	while (current)
	{
		original_str = current->str;
		if (ft_strncmp(original_str, "<<", 2) == 0
			&& ft_strlen(original_str) == 2)
		{
			current = current->next->next;
			continue ;
		}
		exp = init_expansion(current->str);
		current->str = expand_str(shell, exp);
		free(exp);
		free(original_str);
		if (!current->str)
			return (-1);
		current = current->next;
	}
	return (0);
}
