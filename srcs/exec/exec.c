/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 22:31:02 by irkalini          #+#    #+#             */
/*   Updated: 2025/03/28 00:44:37 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_builtin(t_shell *shell,char **args)
{
	if (ft_strncmp(args[0], "echo", 4) == 0 && ft_strlen(args[0]) == 4)
		echo_cmd(args);
	else if (ft_strncmp(args[0],"env", 3) == 0 && ft_strlen(args[0]) == 3)
		env_cmd(shell);
	else if (ft_strncmp(args[0],"pwd", 3) == 0 && ft_strlen(args[0]) == 3)
		pwd_cmd();
	else if (ft_strncmp(args[0],"cd", 2) == 0 && ft_strlen(args[0]) == 2)
		cd_cmd(args);
	else if (ft_strncmp(args[0],"export", 6) == 0 && ft_strlen(args[0]) == 6)
		export_cmd(shell,args);
	else if (ft_strncmp(args[0],"unset", 5) == 0 && ft_strlen(args[0]) == 5)
		unset_cmd(shell, args);
	else if (ft_strncmp(args[0],"exit", 4) == 0 && ft_strlen(args[0]) == 4)
			exit(0);
}

char	*get_ex_path(char *cmd)
{
	char	*path_env;
	char	*path;
	char	**tmp;
	int		i;

	i = 0;
	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	tmp = ft_split(path_env, ':');
	path = NULL;
	while (tmp[i])
	{
		path = ft_strjoin(tmp[i], "/");
		path = ft_strjoin(path, cmd);
		if (access(path, F_OK | X_OK) == 0)
		{
			free_split(tmp);
			return (path);
		}
		free(path);
		i++;
	}
	free_split(tmp);
	return (NULL);
}

char	*get_path(char *cmd)
{
	char	*path;

	if (ft_strchr(cmd, '/'))
	{
		path = ft_strdup(cmd);
		if (access(path, F_OK | X_OK) == -1)
		{
			printf("minishell: %s: command not found\n", path);
			free(path);
			return (NULL);
		}
	}
	else
	{
		path = get_ex_path(cmd);
		if (!path)
		{
			printf("minishell: %s: command not found\n", cmd);
			return (NULL);
		}
	}
	return (path);
}

void	exec_cmd_ex(t_shell *shell, char **args)
{
	char	*path;
	int		pid;
	int		status;

	path = get_path(args[0]);
	if (!path)
		return ;
	pid = fork();
	if (pid == 0)
	{
		execve(path, args, shell->my_environ);
		free(path);
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		waitpid(pid,&status, 0);
		free(path);
	}
	else
	{
		perror("fork");
		free(path);
	}
}

// void	execute(t_shell *shell, char **args)
// {
// 	if (is_builtin(args))
// 		exec_builtin(shell,args);
// 	// else if (redirection)
// 	else
// 		exec_cmd_ex(shell,args);
// }


// Helper function to set up input redirections
int setup_input_redirections(t_command *cmd) {
    t_redirection *input_redir = cmd->input;
    int fd;

    while (input_redir != NULL) {
        fd = open(input_redir->file, O_RDONLY);
        if (fd == -1) {
            perror("open (input)");
            return -1;  // Indicate error
        }

        if (dup2(fd, STDIN_FILENO) == -1) {
            perror("dup2 (input)");
            close(fd);
            return -1;
        }

        close(fd);  // Close the original file descriptor
        input_redir = input_redir->next;
    }
    return 0; //Success
}

// Helper function to set up output redirections
int setup_output_redirections(t_command *cmd) {
    t_redirection *output_redir = cmd->output;
    int fd;
    int flags;

    while (output_redir != NULL) {
        flags = O_WRONLY | O_CREAT;
        if (output_redir->append) {
            flags |= O_APPEND;
        } else {
            flags |= O_TRUNC;
        }

        fd = open(output_redir->file, flags, 0644);
        if (fd == -1) {
            perror("open (output)");
            return -1;
        }

        if (dup2(fd, STDOUT_FILENO) == -1) {
            perror("dup2 (output)");
            close(fd);
            return -1;
        }

        close(fd);
        output_redir = output_redir->next;
    }
    return 0;
}

void	execute(t_shell *shell, t_command *cmd)
{
    int saved_stdin = dup(STDIN_FILENO);   // Save original stdin
    int saved_stdout = dup(STDOUT_FILENO); // Save original stdout
    int status = 0;
    bool restore_needed = false; // Flag to indicate if we need to restore stdout/stdin

    if (saved_stdin == -1 || saved_stdout == -1) {
        perror("dup");
        return; // Or handle the error in a more appropriate way
    }

    if (cmd == NULL || cmd->args == NULL) {
        close(saved_stdin);
        close(saved_stdout);
        return;
    }

    if (is_builtin(cmd->args)) {
        exec_builtin(shell,cmd->args);
    } else {
        // Set up input redirections
        if (cmd->input) {
            if (setup_input_redirections(cmd) == -1) {
                status = 1;
                restore_needed = true;
            }
        }

        // Set up output redirections
        if (status == 0 && cmd->output) {  // Only proceed if input redirections were successful
            if (setup_output_redirections(cmd) == -1) {
                status = 1;
                restore_needed = true;
            }
        }

        if (status == 0) { // Execute external command if redirections were successful
            exec_cmd_ex(shell,cmd->args);
        }

       if (restore_needed) { //Restore stdout/stdin if needed

            dup2(saved_stdin, STDIN_FILENO);  // Restore original stdin
            dup2(saved_stdout, STDOUT_FILENO); // Restore original stdout
        }
        close(saved_stdin);
        close(saved_stdout);
    }
}
