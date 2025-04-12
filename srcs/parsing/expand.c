/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:20:15 by enrmarti          #+#    #+#             */
/*   Updated: 2025/04/12 22:23:56 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


//KEEPS TRACK WHETHER WE ARE INSIDE OF QUOTES OR NOT 
void    handle_quotes(t_expansion *exp)
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

bool	check_quotes_inquotes(t_expansion *exp)
{
	char	*token;
	int		i;
		
	i = exp->i;
	token = exp->token;
	if (token[i] == '\'' && exp->in_single_quote)
	{
		exp->res = append_char(exp->res, '$');
		exp->i++;
		exp->in_single_quote = !exp->in_single_quote;
		return (true);
	}
	else if (token[i] == '"' && exp->in_double_quote)
	{
		exp->res = append_char(exp->res, '$');
		exp->i++;
		exp->in_double_quote = !exp->in_double_quote;
		return (true);
	}
	return (false);
}

//HANDLES (SKIPS) THE $'' AND $"" VARS
bool	check_dollar_quotes(t_expansion *exp)
{
	char	*token;
	int		i;
	
	i = exp->i;
	token = exp->token;
	if (token[i + 1] && token[i] == '\'' && token[i + 1] == '\'')
	{
		exp->i += 2;
		return (true);
	}
	else if (token[i + 1] && token[i] == '"' && token[i + 1] == '"')
	{
		exp->i += 2;
		return (true);
	}
	return (false);
}

//HANDLES STANDARD ENV VARS, $HOME $dontexist etc
void    default_var(t_shell *shell, t_expansion *exp)
{
    char    *var_name;
    char    *value;
    int     start_index;
    int     len;

    start_index = exp->i;
    while (exp->token[exp->i] && (ft_isalnum(exp->token[exp->i]) || exp->token[exp->i] == '_'))
        exp->i++;
    len = exp->i - start_index;
    var_name = ft_substr(&exp->token[start_index], 0, len);
    value = echo_env_val(shell, var_name);
    free(var_name);
    if (value)
        exp->res = new_strjoin(exp->res, value);
}

//HANDLES CASES SUCH AS $$, $?, $=, etc
void	handle_var_expansion(t_shell *shell, t_expansion *exp)
{
	pid_t	pid;
	char	*value;
	
	exp->i++;
	if (check_quotes_inquotes(exp) || check_dollar_quotes(exp))
		return ;
	if (exp->token[exp->i] == '?')
	{
		value = ft_itoa(shell->exit_status);
		exp->res = new_strjoin(exp->res, value);
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
			handle_var_expansion(shell, exp);
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
