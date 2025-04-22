/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uid.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:16:51 by enrmarti          #+#    #+#             */
/*   Updated: 2025/04/22 14:11:45 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_uid(void)
{
	struct stat	file_info;
	char		cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getuid getcwd");
		return (-1);
	}
	if (stat(cwd, &file_info) == -1)
	{
		perror("getuid stat");
		return (-1);
	}
	return (file_info.st_uid);
}
