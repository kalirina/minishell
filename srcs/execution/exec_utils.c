/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:55:52 by irkalini          #+#    #+#             */
/*   Updated: 2025/04/01 07:26:05 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_builtin_name(const char *arg0, const char *builtin_name)
{
	size_t	len;

	len = ft_strlen(builtin_name);
	if (ft_strncmp(arg0, builtin_name, len) == 0 && arg0[len] == '\0')
		return (1);
	return (0);
}

int	is_builtin(char **args)
{
	if (!args || !args[0])
		return (0);
	if (check_builtin_name(args[0], "echo"))
		return (1);
	if (check_builtin_name(args[0], "cd"))
		return (1);
	if (check_builtin_name(args[0], "pwd"))
		return (1);
	if (check_builtin_name(args[0], "export"))
		return (1);
	if (check_builtin_name(args[0], "unset"))
		return (1);
	if (check_builtin_name(args[0], "env"))
		return (1);
	if (check_builtin_name(args[0], "exit"))
		return (1);
	return (0);
}

void	free_split(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
