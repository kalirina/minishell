/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_backup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:55:29 by enrmarti          #+#    #+#             */
/*   Updated: 2025/04/24 21:19:01 by irkalini         ###   ########.fr       */
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

char	*get_heredoc_input(t_shell *shell, const char *delimiter)
{
	char	*line;
	char	*result;
	char	*expanded;
	int		delimiter_length;

	result = NULL;
	delimiter_length = ft_strlen(delimiter);
	signal(SIGINT, handle_heredoc_sigint);
	while (1)
	{
		line = readline("> ");
		if (g_heredoc_interrupt)
			break ;
		if (!line)
		{
			printf("minishell: here-document delimited by end-of-file (wanted `%s')\n", delimiter);
			return (result);
		}
		if (line && strncmp(line, delimiter, delimiter_length) == 0
			&& ft_strlen(line) == delimiter_length)
			return (free(line),result);
		expanded = expand_heredoc_line(shell, line, ft_strlen(line));
		result = new_strjoin(result, expanded);
		free(expanded);
		result = new_strjoin(result, "\n");
	}
	return (result);
}

char	*heredoc_fork(t_shell *shell, char *delimiter, t_executer *ex)
{
	char	*result;
	char	*tmp;
	pid_t	child_pid;

	result = NULL;
	child_pid = fork();
	if (child_pid == -1)
		return (perror("fork failed"), NULL);
	else if (child_pid == 0)
	{
		signal(SIGINT, handle_heredoc_sigint);
		tmp = get_heredoc_input(shell, delimiter);
		result = tmp;
		free(tmp);
		ft_exit(shell, 0, ex);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(child_pid, NULL, 0);
		if (g_heredoc_interrupt)
			return (NULL);
	}
	signal(SIGINT, handle_sigint);
	return (result);
}

int	handle_heredoc(t_shell *shell, t_redirection *red, t_executer *ex)
{
	int		fd;
	char	*heredoc_content;

	heredoc_content = heredoc_fork(shell, red->file, ex);
	if (heredoc_content == NULL)
		return (-1);
	fd = open(".temp_heredoc", O_CREAT | O_TRUNC | O_WRONLY, 0600);
	if (fd == -1)
	{
		(perror("Error exec: open (heredoc)"), free(heredoc_content));
		return (-1);
	}
	if (write(fd, heredoc_content, ft_strlen(heredoc_content)) == -1)
	{
		(perror("Error exec: write (heredoc)"), free(heredoc_content));
		(close(fd), unlink(".temp_heredoc"));
		return (-1);
	}
	close(fd);
	free(heredoc_content);
	fd = open(".temp_heredoc", O_RDONLY);
	unlink(".temp_heredoc");
	return (fd);
}
