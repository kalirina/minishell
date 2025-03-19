/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 23:59:02 by irkalini          #+#    #+#             */
/*   Updated: 2025/03/19 19:35:28 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_environ(t_shell *shell)
{
	extern char	**environ;
	int			i;

	i = 0;
	while (environ[i])
		i++;
	shell->my_environ = malloc(sizeof(char *) * (i+1));
	if (!shell->my_environ)
		return ;
	i = 0;
	while (environ[i])
	{
		shell->my_environ[i] = ft_strdup(environ[i]);
		i++;
	}
	shell->my_environ[i] = NULL;
}

void	sync_my_environ(t_shell *shell)
{
	extern char	**environ;
	int	i;

	i = 0;
	if (shell->my_environ)
	{
		while (shell->my_environ[i])
			free(shell->my_environ[i++]);
		free(shell->my_environ);
	}
	i = 0;
	while (environ[i])
		i++;
	shell->my_environ = malloc(sizeof(char *) * (i+1));
	if (!shell->my_environ)
		return ;
	i = 0;
	while (environ[i])
	{
		shell->my_environ[i] = ft_strdup(environ[i]);
		i++;
	}
	shell->my_environ[i] = NULL;
}

void	env_cmd(t_shell *shell)
{
	int			i;

	i = 0;
	while (shell->my_environ[i])
	{
		printf("%s\n", shell->my_environ[i]);
		i++;
	}
	printf("My function\n");
}
