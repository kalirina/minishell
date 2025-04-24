/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:28:36 by enrmarti          #+#    #+#             */
/*   Updated: 2025/04/24 23:35:35 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_var_name(char *start)
{
	int	len;

	len = 0;
	while (start[len] && (isalnum(start[len]) || start[len] == '_'))
	len++;
	return (ft_substr(start, 0, len));
}

void	default_heredoc_var(t_shell *shell, char *line, char **res, int *i)
{
	char	*var_name;
	char	*value;

	var_name = get_var_name(&line[*i]);
	value = NULL;
	if (ft_strncmp(var_name, "UID", 3) == 0 && ft_strlen(var_name) == 3)
		value = ft_itoa(shell->uid);
	else
		value = echo_env_val(shell, var_name);
	if (value)
	{
		*res = new_strjoin(*res, value);
		free(value);
	}
	(*i) += ft_strlen(var_name);
	free(var_name);
}

void	expand_heredoc_var(t_shell *shell, char *line, char **res, int *i)
{
	char	*value;

	if (!line[*i] || line[*i] == '='
		|| line[*i] == ':' || line[*i] == ' ')
		*res = append_char(*res, '$');
	else if (ft_isdigit(line[*i]))
		(*i)++;
	else if (line[*i] == '?')
	{
		value = ft_itoa(shell->exit_status);
		*res = new_strjoin(*res, value);
		free(value);
		(*i)++;
	}
	else if (line[*i] == '$')
	{
		value = ft_itoa(getpid());
		*res = new_strjoin(*res, value);
		free(value);
		(*i)++;
	}
	else
		default_heredoc_var(shell, line, res, i);
}

char	*expand_heredoc_line(t_shell *shell, char *line, int len)
{
	int		i;
	char	*res;

	i = 0;
	res = ft_strdup("");
	if (!res)
		return (NULL);
	while (i < len)
	{
		if (line[i] == '\\')
		{
			if (!line[i + 1])
				return (free(line), res);
			res = append_char(res, line[i + 1]);
			i += 2;
		}
		else if (line[i] == '$')
		{
			i++;
			expand_heredoc_var(shell, line, &res, &i);
		}
		else
			res = append_char(res, line[i++]);
	}
	return (free(line), res);
}
