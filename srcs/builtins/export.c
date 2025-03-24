/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 20:44:35 by irkalini          #+#    #+#             */
/*   Updated: 2025/03/23 21:11:11 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	export_no_arg(t_shell *shell)
{
	char	*line;
	char	*val;
	int		i;

	i = 0;
	while (shell->my_environ[i])
	{
		line = ft_strdup(shell->my_environ[i]);
		val = ft_strchr(line, '=');
		if (val)
		{
			*val = '\0';
			printf("declare -x %s=\"%s\"\n", line, val + 1);
		}
		else
			printf("declare -x %s\n", line);
		free(line);
		i++;
	}
}

char	*get_var(char *arg)
{
	char	*var;
	char	*val;

	val = ft_strchr(arg, '=');
	if (val)
		var = ft_substr(arg, 0, val - arg);
	else
		var= ft_strdup(arg);
	return (var);
}

char	*get_val(char *arg)
{
	char	*val;
	char	*sign;

	sign = ft_strchr(arg, '=');
	if (!sign || !*(sign + 1))
		return (NULL);
	val = ft_strdup(sign + 1);
	return (val);
}

int	add_var(t_shell *shell, char *arg)
{
	char	*var;
	char	*val;
	int		i;

	i = 0;
	var = get_var(arg);
	val = get_val(arg);
	if (!var || !is_valid_var(var))
		return (free(var), free(val), 0);
	while (shell->my_environ[i])
	{
		if (ft_strncmp(shell->my_environ[i], var, ft_strlen(var)) == 0
			&& (shell->my_environ[i][ft_strlen(var)] == '='
			|| shell->my_environ[i][ft_strlen(var)] == '\0'))
		{
			update_env_var(shell, i, var, val);
			return (free(var), free(val), 1);
		}
		i++;
	}
	add_new_env_var(shell, i, var, val);
	return (free(var), free(val), 1);
}

void	export_cmd(t_shell *shell,char **args)
{
	int		i;

	if (!args[1])
		return (export_no_arg(shell));
	i = 1;
	while (args[i])
	{
		if (!ft_strchr(args[i], '='))
		{
			if (!add_var(shell, args[i]))
				printf("export: '%s': not a valid identifier\n", args[i]);
		}
		else
		{
			if (!add_var(shell, args[i]))
				printf("export: '%s': not a valid identifier\n", args[i]);
		}
		i++;
	}
	printf("My function\n");
}
