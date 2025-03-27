/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 22:31:02 by irkalini          #+#    #+#             */
/*   Updated: 2025/03/27 01:50:00 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_builtin(t_shell *shell,char **args)
{
	if (ft_strncmp(args[0], "echo", 4) == 0 && ft_strlen(args[0]) == 4)
	{
		echo_cmd(shell);
		shell->exit_status = 0;
	}
	else if (ft_strncmp(args[0],"env", 3) == 0 && ft_strlen(args[0]) == 3)
	{
		env_cmd(shell);
		shell->exit_status = 0;
	}
	else if (ft_strncmp(args[0],"pwd", 3) == 0 && ft_strlen(args[0]) == 3)
	{
		pwd_cmd();
		shell->exit_status = 0;
	}
	else if (ft_strncmp(args[0],"cd", 2) == 0 && ft_strlen(args[0]) == 2)
	{
		if (cd_cmd(shell) == -1) // Assume cd_cmd returns -1 on failure
			shell->exit_status = 1; // Non-zero for failure
		else
			shell->exit_status = 0;
	}
	else if (ft_strncmp(args[0],"export", 6) == 0 && ft_strlen(args[0]) == 6)
		export_cmd(shell,args);
	else if (ft_strncmp(args[0],"unset", 5) == 0 && ft_strlen(args[0]) == 5)
		unset_cmd(shell, args);
	else if (ft_strncmp(args[0],"exit", 4) == 0 && ft_strlen(args[0]) == 4)
			exit(0); //another function
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
	{
		shell->exit_status = 127;
		return ;
	}
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
		if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
		else
			shell->exit_status = 1;
		free(path);
	}
	else
	{
		perror("fork");
		free(path);
		shell->exit_status = 1;
	}
}

void	execute(t_shell *shell)
{
	if (is_builtin(shell->cmd->args))
		exec_builtin(shell,shell->cmd->args);
	// else if (redirection)
	else
		exec_cmd_ex(shell,shell->cmd->args);
}

