/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:55:29 by enrmarti          #+#    #+#             */
/*   Updated: 2025/04/21 20:43:53 by enrmarti         ###   ########.fr       */
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

// char	*get_var_name(char *start)
// {
// 	int	len;

// 	len = 0;
// 	while (start[len] && (isalnum(start[len]) || start[len] == '_'))
// 		len++;
// 	return (ft_substr(start, 0, len));
// }
// char	*expand_heredoc_var(char *line, char **res, int *i)
// {
// 	if (line[i] == '$')
// 		res = new_node(line)
// }

// char	*expand_heredoc_line(char *line)
// {
// 	int		i;
// 	int		len;
// 	char	*res;

// 	len = ft_strlen(line);
// 	i = 0;
// 	res = ft_strdup("");
// 	if (!res)
// 		return ;
// 	while (i < len)
// 	{
// 		if (line[i] == '\\')
// 		{
// 			if (!line[i + 1])
// 				return (res);
// 			res = append_char(res, line[i + 1]);
// 			i += 2;
// 		}
// 		else if (line[i] == '$')
// 		{
// 			i++;
// 			expand_heredoc_var(line, &res, &i);
// 		}
// 		else	
// 	}
// 	return (res);
// }

char	*get_exec_path(t_shell *shell, char *cmd)
{
	char	*path;

	if (!cmd || !cmd[0])
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		path = ft_strdup(cmd);
		if (!path)
			return (perror("minishell: ft_strdup failed"), NULL);
		if (access(path, F_OK) == -1)
			print_error(NULL, path, strerror(errno));
		else if (access(path, X_OK) == -1)
			print_error(NULL, path, strerror(errno));
		else
			return (path);
		return (free(path), NULL);
	}
	else
	{
		path = find_cmd_in_path(shell, cmd);
		if (!path)
			return (print_error(cmd, NULL, "command not found"), NULL);
		return (path);
	}
	return (path);
}

void	handle_exec_status(t_shell *shell, int status)
{
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
	else if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
		write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_status = 128 + WTERMSIG(status);
	else
		shell->exit_status = 1;
}
