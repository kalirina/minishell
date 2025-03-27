/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:17:24 by irkalini          #+#    #+#             */
/*   Updated: 2025/03/27 03:27:07 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_valid_var(char *name)
{
	int	i;

	if (!name || !name[0] || (!ft_isalpha(name[0]) && name[0] != '_'))
		return (0);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	remove_var(t_shell *shell, int i)
{
	if (!shell || !shell->my_environ || i < 0)
		return ;
	free(shell->my_environ[i]);
	while (shell->my_environ[i])
	{
		shell->my_environ[i] = shell->my_environ[i + 1];
		i++;
	}
}

int	unset_cmd(t_shell *shell, char **args)
{
	int	i;
	int	index;

	if (!args[1])
		return (0);
	i = 1;
	while (args[i])
	{
		if (!is_valid_var(args[i]))
			print_error("unset", args[i], "not a valid identifier");
		else
		{
			index = find_env_var_index(shell->my_environ, args[i]);
			if (index != -1)
				remove_var(shell, index);
		}
		i++;
	}
	return (0);
}
