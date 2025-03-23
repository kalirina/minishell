/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 22:31:02 by irkalini          #+#    #+#             */
/*   Updated: 2025/03/23 22:22:23 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	char	*cpy;

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

void	execute(t_shell *shell, char **args)
{
	if (is_builtin(args))
		exec_builtin(shell,args);
	// else if (redirection)
	else
		exec_cmd_ex(shell,args);
}

