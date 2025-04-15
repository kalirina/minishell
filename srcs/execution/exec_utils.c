/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:55:52 by irkalini          #+#    #+#             */
/*   Updated: 2025/04/15 17:23:19 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_builtin_name(const char *arg0, const char *builtin_name)
{
	size_t	len;

	len = ft_strlen(builtin_name);
	if (ft_strncmp(arg0, builtin_name, len) == 0 && arg0[len] == '\0')
		return (1);
	return (0);
}

int	is_builtin(char **args)
{
	if (!args || !args[0])
		return (0);
	if (check_builtin_name(args[0], "echo"))
		return (1);
	if (check_builtin_name(args[0], "cd"))
		return (1);
	if (check_builtin_name(args[0], "pwd"))
		return (1);
	if (check_builtin_name(args[0], "export"))
		return (1);
	if (check_builtin_name(args[0], "unset"))
		return (1);
	if (check_builtin_name(args[0], "env"))
		return (1);
	if (check_builtin_name(args[0], "exit"))
		return (1);
	return (0);
}

void	free_split(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

t_executer	*init_executer(t_command *cmds)
{
	t_executer	*ex;

	ex = malloc(sizeof(t_executer));
	if (!ex)
		return (NULL);
	ex->cmds = cmds;
	ex->n_commands = count_commands(cmds);
	ex->saved_stdin = dup(STDIN_FILENO);
	ex->saved_stdout = dup(STDOUT_FILENO);
	if (ex->saved_stdin == -1 || ex->saved_stdout == -1) {
		perror("dup");
		if (ex->saved_stdin != -1) close(ex->saved_stdin);
		if (ex->saved_stdout != -1) close(ex->saved_stdout);
		return (NULL);
	}
	ex->pipe_in_fd = -1;
	ex->pipe_out_fd = -1;	
	if (ex->n_commands > 1)
		ex->pipe = true;
	else
		ex->pipe = false;
	return (ex);
}
