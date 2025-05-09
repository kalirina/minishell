/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 23:27:10 by enrmarti          #+#    #+#             */
/*   Updated: 2025/04/24 23:32:46 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	check_empty_cmd(t_shell *shell, char *cmd)
{
	int	flag;
	int	i;

	if (!cmd || !cmd[0])
		return (print_error(cmd, NULL, "command not found"), true);
	flag = 1;
	i = 0;
	while (cmd[i] && flag)
	{
		if (!is_space(cmd[i]))
			flag = 0;
		i++;
	}
	if (flag == 1)
	{
		shell->exit_status = 0;
		shell->skip_cmd = true;
		return (true);
	}
	return (false);
}

char	*get_exec_path(t_shell *shell, char *cmd)
{
	char	*path;

	if (check_empty_cmd(shell, cmd))
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

int	safe_open(char *name)
{
	int	fd;

	fd = open(name, O_RDONLY);
	if (fd == -1)
	{
		printf(RED "minishell: %s: No such file or directory\n" RES, name);
		return (-1);
	}
	return (fd);
}
