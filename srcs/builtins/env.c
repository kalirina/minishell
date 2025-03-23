/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 23:59:02 by irkalini          #+#    #+#             */
/*   Updated: 2025/03/23 21:11:03 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_env_var(t_shell *shell, int i, char *var, char *val)
{
	char	*new;

	free(shell->my_environ[i]);
	if (val)
		new = ft_strjoin(ft_strjoin(var, "="), val);
	else
		new = ft_strdup(var);
	shell->my_environ[i] = new;
}

void	add_new_env_var(t_shell *shell, int i, char *var, char *val)
{
	char	**new_environ;
	char	*new_var;

	new_environ = ft_calloc(i + 2, sizeof(char *));
	ft_memcpy(new_environ, shell->my_environ, i * sizeof(char *));
	if (val)
		new_var = ft_strjoin(ft_strjoin(var, "="), val);
	else
		new_var = ft_strdup(var);
	new_environ[i] = new_var;
	new_environ[i + 1] = NULL;
	free(shell->my_environ);
	shell->my_environ = new_environ;
}

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
