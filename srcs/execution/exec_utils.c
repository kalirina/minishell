/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:55:52 by irkalini          #+#    #+#             */
/*   Updated: 2025/03/23 19:31:04 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(char **args)
{
	if ((ft_strncmp(args[0], "echo", 4) == 0 && ft_strlen(args[0]) == 4) ||
		(ft_strncmp(args[0],"env", 3) == 0 && ft_strlen(args[0]) == 3) ||
		(ft_strncmp(args[0],"pwd", 3) == 0 && ft_strlen(args[0]) == 3) ||
		(ft_strncmp(args[0],"cd", 2) == 0 && ft_strlen(args[0]) == 2) ||
		(ft_strncmp(args[0],"export", 6) == 0 && ft_strlen(args[0]) == 6) ||
		(ft_strncmp(args[0], "unset", 5) == 0 && ft_strlen(args[0]) == 5) ||
		(ft_strncmp(args[0],"exit", 4) == 0 && ft_strlen(args[0]) == 4))
		return (1);
	return (0);
}

void	free_split(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
