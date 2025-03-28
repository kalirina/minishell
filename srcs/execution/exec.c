/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 22:31:02 by irkalini          #+#    #+#             */
/*   Updated: 2025/03/28 20:14:07 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	execute_builtin_cmd(t_shell *shell, char **args)
{
	int	status;

	status = 1;
	if (check_builtin_name(args[0], "echo"))
		status = echo_cmd(shell);
	else if (check_builtin_name(args[0], "cd"))
		status = cd_cmd(shell);
	else if (check_builtin_name(args[0], "pwd"))
		status = pwd_cmd();
	else if (check_builtin_name(args[0], "export"))
		status = export_cmd(shell, args);
	else if (check_builtin_name(args[0], "unset"))
		status = unset_cmd(shell, args);
	else if (check_builtin_name(args[0], "env"))
		status = env_cmd(shell);
	else if (check_builtin_name(args[0], "exit"))
		status = exit_cmd(shell, args);
	return (status);
}

static char *check_path_entry(const char *dir, const char *cmd, char **paths)
{
	char	*full_path;

	full_path = ft_strjoin(dir, "/");
	if (!full_path)
		return (perror("minishell: malloc failed"), NULL);
	full_path = ft_strjoin(full_path, cmd);
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


	path_env = get_env_var_value(shell->my_environ, "PATH");;
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

void	exec_ext_cmd(t_shell *shell, char **args)
{
	char	*path;
	int		pid;
	int		status;

	path = get_exec_path(shell, args[0]);
	if (!path)
	{
		shell->exit_status = 127;
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		free(path);
		shell->exit_status = 1;
	}
	if (pid == 0)
	{
		execve(path, args, shell->my_environ);
		print_error(args[0], NULL, strerror(errno));
		free(path);
		if (errno == EACCES)
			exit(126);
		exit(127);
	}
	else
	{
		waitpid(pid,&status, 0);
		if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			shell->exit_status = 128 + WTERMSIG(status);
		else
			shell->exit_status = 1;
		free(path);
	}
}

void	execute(t_shell *shell)
{
	int saved_stdin = dup(STDIN_FILENO);   // Save original stdin
    int saved_stdout = dup(STDOUT_FILENO); // Save original stdout
    int status = 0;
    bool restore_needed = false; // Flag to indicate if we need to restore stdout/stdin

    if (saved_stdin == -1 || saved_stdout == -1) {
        perror("dup");
        return; // Or handle the error in a more appropriate way
    }

    if (shell->cmd == NULL || shell->cmd->args == NULL) {
        close(saved_stdin);
        close(saved_stdout);
        return;
    }

	if (is_builtin(shell->cmd->args))
		shell->exit_status = execute_builtin_cmd(shell, shell->cmd->args);
	else {
        // Set up input redirections
        if (shell->cmd->input) {
            if (setup_input_redirections(shell->cmd) == -1) {
                status = 1;
                restore_needed = true;
            }
        }

        // Set up output redirections
        if (status == 0 && shell->cmd->output) {  // Only proceed if input redirections were successful
            if (setup_output_redirections(shell->cmd) == -1) {
                status = 1;
                restore_needed = true;
            }
        }

        if (status == 0) { // Execute external command if redirections were successful
            exec_ext_cmd(shell, shell->cmd->args);
        }

       if (restore_needed) { //Restore stdout/stdin if needed

            dup2(saved_stdin, STDIN_FILENO);  // Restore original stdin
            dup2(saved_stdout, STDOUT_FILENO); // Restore original stdout
        }
        close(saved_stdin);
        close(saved_stdout);
    }
}

