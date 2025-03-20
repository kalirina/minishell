/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 22:31:02 by irkalini          #+#    #+#             */
/*   Updated: 2025/03/20 10:08:28 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(char **args)
{
	if ((ft_strncmp(args[0], "echo", 4) == 0 && ft_strlen(args[0]) == 4) ||
		(ft_strncmp(args[0],"env", 3) == 0 && ft_strlen(args[0]) == 3) ||
		(ft_strncmp(args[0],"pwd", 3) == 0 && ft_strlen(args[0]) == 3) ||
		(ft_strncmp(args[0],"cd", 2) == 0 && ft_strlen(args[0]) == 2) ||
		(ft_strncmp(args[0],"export", 6) == 0 && ft_strlen(args[0]) == 6) ||
		(ft_strncmp(args[0],"exit", 4) == 0 && ft_strlen(args[0]) == 4))
		return (1);
	return (0);
}

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
	else if (ft_strncmp(args[0],"exit", 4) == 0 && ft_strlen(args[0]) == 4)
			exit(0); //another function
}

char	*get_ex_path(char *cmd)
{
	char	*path;
	char	*copy;
	char	**tmp;
	int		i;

	path = malloc(sizeof(char) * 1024);
	if (!path)
		return (NULL);
	path = getenv(cmd);
	tmp = ft_split(path,':');
	free(path);
	copy = ft_strjoin("/", cmd);
	while (tmp[i])
	{
		path = ft_strjoin(tmp[i], copy);
		if ((access(path, F_OK)== -1) || (access(path, X_OK) == -1))
			i++;
		else
			return (path);
	}
	return (NULL);
}

void	exec_cmd_ex(t_shell *shell, char **args)
{
	char	*path;
	int		pid;
	int		status;

	//if user provides abs or rel path no need to search
	path = get_ex_path(args[0]);
	if (!path)
		ft_printf("no such command");
	pid = fork();
	if (pid == 0) //if child
	{
		printf("caca");
		if (execve(args[0], args, shell->my_environ) == -1)
			exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid,&status, 0);
		// if (ft_strncmp(args[0], "export", 6) == 0 && ft_strlen(args[0]) == 6)
		// 	sync_my_environ(shell);
	}
}

void	execute(t_shell *shell, char **args)
{
	if (is_builtin(args))
		exec_builtin(shell,args);
	else
	{
		exec_cmd_ex(shell,args);
	}
}

