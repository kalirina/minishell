/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 23:59:02 by irkalini          #+#    #+#             */
/*   Updated: 2025/04/24 17:49:15 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	copy_environ_vars(t_shell *shell, char **environ, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		shell->my_environ[i] = ft_strdup(environ[i]);
		if (!shell->my_environ[i])
		{
			perror("minishell: init_environ: ft_strdup failed");
			while (--i >= 0)
				free(shell->my_environ[i]);
			return (1);
		}
		i++;
	}
	shell->my_environ[i] = NULL;
	return (0);
}

void	init_environ(t_shell *shell, char **environ)
{
	int			i;
	int			count;

	i = 0;
	count = 0;
	while (environ && environ[i])
		i++;
	count = i;
	shell->my_environ = malloc(sizeof(char *) * (count + 1));
	if (!shell->my_environ)
	{
		perror("minishell: init_environ: malloc failed");
		cleanup_shell(shell);
		exit(EXIT_FAILURE);
	}
	if (copy_environ_vars(shell, environ, count) != 0)
	{
		cleanup_shell(shell);
		exit(EXIT_FAILURE);
	}
}

int	env_cmd(t_shell *shell)
{
	int	i;

	if (shell->cmd->args[1])
	{
		print_error("env", shell->cmd->args[1], "No such file or directory");
		return (127);
	}
	i = 0;
	while (shell->my_environ && shell->my_environ[i])
	{
		if (ft_strchr(shell->my_environ[i], '='))
			printf("%s\n", shell->my_environ[i]);
		i++;
	}
	return (0);
}
