/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:55:52 by irkalini          #+#    #+#             */
/*   Updated: 2025/04/21 18:28:20 by irkalini         ###   ########.fr       */
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

char	*check_path_entry(const char *dir, const char *cmd, char **paths)
{
	char	*full_path;
	char	*tmp;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (perror("minishell: malloc failed"), NULL);
	full_path = ft_strjoin(tmp, cmd);
	free(tmp);
	if (!full_path)
		return (perror("minishell: malloc failed"), NULL);
	if (access(full_path, X_OK) == 0)
		return (free_split(paths), full_path);
	free(full_path);
	return (NULL);
}

char	*find_cmd_in_path(t_shell *shell, char *cmd)
{
	char	*path_env;
	char	*res_path;
	char	**paths;
	int		i;

	path_env = get_env_var_value(shell->my_environ, "PATH");
	if (!path_env)
		return (NULL);
	if (*path_env == '\0')
		return (free(path_env), NULL);
	paths = ft_split(path_env, ':');
	free(path_env);
	if (!paths)
		return (perror("minishell: ft_split failed"), NULL);
	i = 0;
	res_path = NULL;
	while (paths[i])
	{
		res_path = check_path_entry(paths[i], cmd, paths);
		if (res_path)
			return (res_path);
		i++;
	}
	return (free_split(paths), NULL);
}

//INITIALISE THE t_executer STRUCT
t_executer	*init_executer(t_command *cmds)
{
	t_executer	*ex;

	ex = malloc(sizeof(t_executer));
	if (!ex)
		return (NULL);
	ex->cmds = cmds;
	ex->n_cmds = count_commands(cmds);
	ex->saved_stdin = dup(STDIN_FILENO);
	ex->saved_stdout = dup(STDOUT_FILENO);
	if (ex->saved_stdin == -1 || ex->saved_stdout == -1)
	{
		perror("Error exec: saved dup");
		if (ex->saved_stdin != -1)
			close(ex->saved_stdin);
		if (ex->saved_stdout != -1)
			close(ex->saved_stdout);
		free(ex);
		return (NULL);
	}
	if (ex->n_cmds > 1)
		ex->pipe = init_pipes(ex->n_cmds);
	else
		ex->pipe = NULL;
	return (ex);
}
