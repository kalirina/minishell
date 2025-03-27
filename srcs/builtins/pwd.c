/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 22:55:41 by irkalini          #+#    #+#             */
/*   Updated: 2025/03/27 02:45:36 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pwd_cmd(void)
{
	char	*buf;
	char	actual_buf[4097];

	buf = actual_buf;
	if (getcwd(buf, 4097) == NULL)
		return (perror("minishell: pwd"), 1);
	ft_putstr_fd(buf, 1);
	ft_putchar_fd('\n', 1);
	return (0);
}
