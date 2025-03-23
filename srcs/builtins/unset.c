/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:17:24 by irkalini          #+#    #+#             */
/*   Updated: 2025/03/23 19:44:58 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_valid_var(char *name)
{
	int	i;

	if (!name || !(*name == '_' || ft_isalpha(*name)))
		return (0);
	i = 1;
	while (name[i])
	{
		if (!(ft_isalnum(name[i]) || name[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

int	find_var_i(t_shell *shell, char *var)
{
	int	i;
	size_t	len;

	i = 0;
	len = ft_strlen(var);
	while (shell->my_environ[i])
	{
		if (ft_strncmp(shell->my_environ[i], var, len) == 0 &&
			(shell->my_environ[i][len] == '=' ||
			shell->my_environ[i][len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

void	remove_var(t_shell *shell, int i)
{
	free(shell->my_environ[i]);
	while (shell->my_environ[i])
	{
		shell->my_environ[i] = shell->my_environ[i + 1];
		i++;
	}
}

void	unset_cmd(t_shell *shell, char **args)
{
	int	i;
	int	index;

	if (!args[1])
		return ;
	i = 1;
	while (args[i])
	{
		if (!is_valid_var(args[i]))
			printf("unset: `%s': not a valid identifier\n", args[i]);
		else
		{
			index = find_var_i(shell, args[i]);
			if (index != -1)
				remove_var(shell, index);
		}
		i++;
	}
	printf("My function\n");
}
