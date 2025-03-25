/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 22:55:41 by irkalini          #+#    #+#             */
/*   Updated: 2025/03/25 22:28:51 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pwd_cmd(void)
{
	char *buf;

	buf = malloc(sizeof(char) * 1024);
	if (!buf)
		return ;
	if (!getcwd(buf, 1024))
	{
		free(buf);
		return ;
	}
	printf("%s\n", buf);
	free(buf);
}
