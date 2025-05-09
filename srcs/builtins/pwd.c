/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 22:55:41 by irkalini          #+#    #+#             */
/*   Updated: 2025/04/21 19:22:38 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pwd_cmd(char **args)
{
	char	*buf;
	char	actual_buf[4097];

	if (args[1] && args[1][0] == '-')
		return (printf(RED "minishell: pwd: %s invalid option\n" RES,
				args[1]), 1);
	buf = actual_buf;
	if (getcwd(buf, 4097) == NULL)
		return (perror("minishell: pwd"), 1);
	ft_putstr_fd(buf, 1);
	ft_putchar_fd('\n', 1);
	return (0);
}
