/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:55:29 by enrmarti          #+#    #+#             */
/*   Updated: 2025/04/21 19:36:28 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_heredoc_input(const char *delimiter)
{
	char	*line;
	char	*result;
	int		delimiter_length;

	result = NULL;
	delimiter_length = ft_strlen(delimiter);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (line && strncmp(line, delimiter, delimiter_length) == 0
			&& ft_strlen(line) == delimiter_length)
		{
			free(line);
			break ;
		}
		
		result = new_strjoin(result, line);
		result = new_strjoin(result, "\n");
	}
	return (result);
}

char	*get_var_name(char *start)
{
	int	len;

	len = 0;
	while (start[len] && (isalnum(start[len]) || start[len] == '_'))
		len++;
	return (ft_substr(start, 0, len));
}
char	*expand_heredoc_var(char *line, char **res, int *i)
{
	if (line[i] == '$')
		res = new_node(line)
}

char	*expand_heredoc_line(char *line)
{
	int		i;
	int		len;
	char	*res;

	len = ft_strlen(line);
	i = 0;
	res = ft_strdup("");
	if (!res)
		return ;
	while (i < len)
	{
		if (line[i] == '\\')
		{
			if (!line[i + 1])
				return (res);
			res = append_char(res, line[i + 1]);
			i += 2;
		}
		else if (line[i] == '$')
		{
			i++;
			expand_heredoc_var(line, &res, &i);
		}
		else
		
	}
	return (res);
}
