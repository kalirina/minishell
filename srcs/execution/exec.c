/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 22:31:02 by irkalini          #+#    #+#             */
/*   Updated: 2025/04/14 19:18:58 by enrmarti         ###   ########.fr       */
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

int setup_input_redirections(t_command *cmd)
{
	t_redirection *input_redir;
	int fd;
	char *heredoc_content;

	input_redir = cmd->input;
	while (input_redir != NULL)
	{
		if (input_redir->heredoc)
		{
			heredoc_content = get_heredoc_input(input_redir->file);
			if (heredoc_content == NULL)
				return (-1);
			fd = open(".temp_heredoc", O_CREAT | O_TRUNC | O_WRONLY, 0600);
			if (fd == -1)
				return (perror("open (input)"), -1);
			write(fd, heredoc_content, strlen(heredoc_content));
			close(fd);
			free(heredoc_content);
			fd = open(".temp_heredoc", O_RDONLY);
			unlink(".temp_heredoc");
		}
		else
			fd = open(input_redir->file, O_RDONLY);
		if (fd == -1)
			return (perror("open (input)"), -1);
		if (dup2(fd, STDIN_FILENO) == -1) {
            perror("dup2 (input)");
            close(fd);
            return -1;
        }
        close(fd);
        input_redir = input_redir->next;
    }
    return 0;
}


int	setup_output_redirections(t_command *cmd)
{
	t_redirection	*output_redir;
	int				fd;
	int				flags;

	output_redir = cmd->output;
	while (output_redir != NULL)
	{
		flags = O_WRONLY | O_CREAT;
		if (output_redir->append)
			flags |= O_APPEND;
		else
			flags |= O_TRUNC;
		fd = open(output_redir->file, flags, 0644);
		if (fd == -1)
			return (perror("open (output)"), -1);
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("dup2 (output)");
			close(fd);
			return (-1);
		}
		close(fd);
		output_redir = output_redir->next;
	}
	return (0);
}

void	exec_ext_cmd(t_shell *shell, char **args)
{
	char	*path;
	pid_t	pid;
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
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
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

void execute_pipeline(t_shell *shell, int num_commands)
{
	t_command	*current_cmd;
	pid_t		pids[num_commands];
	int			pipefds[num_commands - 1][2];
	int			i;
	int			j;

	current_cmd = shell->cmd;
	i = 0;
	while (i < num_commands - 1)
	{
		if (pipe(pipefds[i++]) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	}
	i = 0;
	while (i < num_commands)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pids[i] == 0)
		{
			if (i > 0)
				dup2(pipefds[i - 1][0], STDIN_FILENO);
			if (i < num_commands - 1)
				dup2(pipefds[i][1], STDOUT_FILENO);
			j = 0;
			while (j < num_commands - 1)
			{
				close(pipefds[j][0]);
				close(pipefds[j++][1]);
			}
			if (setup_input_redirections(current_cmd))
				exit(EXIT_FAILURE);
			if (setup_output_redirections(current_cmd))
				exit(EXIT_FAILURE);
			if (is_builtin(current_cmd->args))
				exit(execute_builtin_cmd(shell, current_cmd->args));
			else
			{
				char *path = get_exec_path(shell, current_cmd->args[0]);
				if (!path)
					exit(127);
				execve(path, current_cmd->args, shell->my_environ);
				perror("execve");
				exit(EXIT_FAILURE);
			}
		}
		current_cmd = current_cmd->next;
		i++;
	}
	i = 0;
	while (i < num_commands - 1)
	{
		close(pipefds[i][0]);
		close(pipefds[i++][1]);
	}
	i = 0;
	while (i < num_commands)
		waitpid(pids[i++], NULL, 0);
}

void	execute_cmd(t_shell	*shell)
{
	t_command	*current_cmd;
	int saved_stdin;
	int saved_stdout;
	int status;
  
	status = 0;
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);


	//ENRICO
	if (saved_stdin == -1 || saved_stdout == -1) {
		perror("dup");
		if (saved_stdin != -1) close(saved_stdin);
		if (saved_stdout != -1) close(saved_stdout);
		return; // Or handle the error in a more appropriate way
	}
  
	current_cmd = shell->cmd;
	if (current_cmd->input)
	{
		if (setup_input_redirections(current_cmd) == -1)
			status = 1;
	}
	if (status == 0 && current_cmd->output)
	{
		if (setup_output_redirections(current_cmd) == -1)
			status = 1;
	}
	if (is_builtin(current_cmd->args))
	{
	g_signal_received = 0;
		shell->exit_status = execute_builtin_cmd(shell, shell->cmd->args);
		if (g_signal_received == SIGINT)
			shell->exit_status = 1;
	}
	else
		exec_ext_cmd(shell, current_cmd->args);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

void    execute(t_shell *shell)
{
	t_command *current_cmd;
	int num_commands;
	
	if (shell->cmd == NULL || shell->cmd->args == NULL)
		return ;
	num_commands = 0;
	current_cmd = shell->cmd;
	while (current_cmd != NULL)
	{
		num_commands++;
		current_cmd = current_cmd->next;
	}
	if (num_commands > 1)
		execute_pipeline(shell, num_commands);
	else
		execute_cmd(shell);
}
