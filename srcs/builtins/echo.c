/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:20:42 by irkalini          #+#    #+#             */
/*   Updated: 2025/03/27 00:11:55 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_valid_n_flag(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	i = 2;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	echo_cmd(t_shell *shell)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (shell->cmd->args[i] && is_valid_n_flag(shell->cmd->args[i]))
	{
		newline = 0;
		i++;
	}
	while (shell->cmd->args[i])
	{
		ft_putstr_fd(shell->cmd->args[i], 1);
		if (shell->cmd->args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', 1);
	return (0);
}
