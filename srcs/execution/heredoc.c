/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:55:29 by enrmarti          #+#    #+#             */
/*   Updated: 2025/04/25 19:03:21 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_heredoc_input(t_shell *shell, char *delimiter, int delimiter_size)
{
	char	*line;
	char	*result;
	char	*expanded;

	result = NULL;
	while (1)
	{
		line = readline("> ");
		if (g_heredoc_interrupt)
			break ;
		if (!line)
		{
			printf("minishell: here-document delimited"
				" by end-of-file (wanted `%s')\n", delimiter);
			return (result);
		}
		if (line && strncmp(line, delimiter, delimiter_size) == 0
			&& ft_strlen(line) == delimiter_size)
			return (free(line), result);
		expanded = expand_heredoc_line(shell, line, ft_strlen(line));
		result = new_strjoin(result, expanded);
		free(expanded);
		result = new_strjoin(result, "\n");
	}
	return (result);
}

void	heredoc_child(t_shell *shell, char *delimiter, t_executer *ex)
{
	int		fd;
	char	*tmp;

	signal(SIGINT, handle_heredoc_sigint);
	g_heredoc_interrupt = 0;
	tmp = get_heredoc_input(shell, delimiter, ft_strlen(delimiter));
	fd = open(".temp_heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
		exit(1);
	if (tmp)
	{
		write(fd, tmp, ft_strlen(tmp));
		free(tmp);
	}
	close(fd);
	if (g_heredoc_interrupt)
	{
		unlink(".temp_heredoc");
		ft_exit_heredoc(shell, 130, ex);
	}
	else
		ft_exit_heredoc(shell, 0, ex);
}

int	heredoc_fork(t_shell *shell, char *delimiter, t_executer *ex)
{
	char	*result;
	pid_t	child_pid;
	int		status;

	result = NULL;
	g_heredoc_interrupt = 0;
	child_pid = fork();
	if (child_pid == -1)
		return (perror("fork failed"), -1);
	else if (child_pid == 0)
		heredoc_child(shell, delimiter, ex);
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(child_pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		{
			shell->exit_status = 130;
			return (-1);
		}
	}
	signal(SIGINT, handle_sigint);
	return (0);
}

int	handle_heredoc(t_shell *shell, t_redirection *red, t_executer *ex)
{
	int	fd;

	if (heredoc_fork(shell, red->file, ex) != 0)
		return (-1);
	fd = open(".temp_heredoc", O_RDONLY);
	if (fd == -1)
	{
		perror("Error exec: open (heredoc)");
		return (-1);
	}
	unlink(".temp_heredoc");
	return (fd);
}

void	preprocess_heredoc(t_shell *shell, t_executer *ex)
{
	t_redirection	*current;
	t_command		*cmds;
	int				fd;

	cmds = shell->cmd;
	while (cmds)
	{
		current = cmds->input;
		while (current)
		{
			if (current->heredoc)
			{
				fd = handle_heredoc(shell, current, ex);
				if (fd == -1)
					return ;
				current->fd_heredoc = fd;
			}
			current = current->next;
		}
		cmds = cmds->next;
	}
}
