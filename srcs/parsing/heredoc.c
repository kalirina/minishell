/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:55:29 by enrmarti          #+#    #+#             */
/*   Updated: 2025/04/03 19:39:31 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *get_heredoc_input(const char *delimiter)
{
	char	*line;
	char	*result;
	char	*tmp;
	int		delimiter_length;

	result = NULL;
	delimiter_length = ft_strlen(delimiter);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break;
		if (line && strncmp(line, delimiter, delimiter_length) == 0 && ft_strlen(line) == delimiter_length)
		{
			free(line);
			break;
		}
		tmp = result;
		result = ft_strjoin(result, line);
		if (tmp)
			free(tmp);
		tmp = result;
		result = ft_strjoin(result, "\n");
		if (tmp)
			free(tmp);
		free(line);
	}
	return (result);
}
