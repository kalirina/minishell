/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 20:44:35 by irkalini          #+#    #+#             */
/*   Updated: 2025/03/20 17:55:57 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	export_no_arg(t_shell *shell)
{
	char	*var;
	char	*val;
	int		i;

	i = 0;
	while (shell->my_environ[i])
	{
		var = get_var(shell->my_environ[i]);
		val = get_val(shell->my_environ);
		if (val)
			printf("declare -x %s=\"%s\"\n", var, val);
		else
			printf("declare -x %s\n", var, val);
		free(var);
		free(val);
		i++;
	}
}

char	*get_var(char *arg)
{
	char	*var;
	int		j;

	j = 0;
	while (arg[j] != '=')
		j++;
	var = malloc(sizeof(char) * (j + 1));
	if (!var)
		return ;
	ft_strlcpy(var, arg, j + 1);
	return (var);
}

char	*get_val(char *arg)
{
	char	*val;
	int		j;

	j = 0;
	k = 0;
	while (arg[j] && arg[j] != '=')
		j++;
	if (!arg[j] || !arg[j + 1])
		return (NULL);
	val = ft_strdup(arg + j + 1);
	return (val);
}

int	add_var(t_shell *shell, char *arg)
{
	char	*var;
	char	*val;
	int		i;

	var = get_var(arg);
	val = get_val(arg);
	if (!var || !val)
	{
		free(var);
		free(val);
		return ;
	}
	while (shell->my_environ[i])
	{
		if (ft_strncmp(shell->my_environ, var, ft_strlen(var)))
			
	}
}

void	export_cmd(t_shell *shell,char **args)
{
	int		i;

	if (!args[1])
	{
		export_no_arg(shell);
		return ;
	}
	i = 1;
	while (args[i])
	{
		if (!ft_strchr(args[i], '='))
			i++;
		else
		{
			add_var(shell, args[i]);
			i++;
		}
	}
}
