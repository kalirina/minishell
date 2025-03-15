/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:58:25 by irkalini          #+#    #+#             */
/*   Updated: 2025/03/15 16:21:46 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../libft/libft.h"

char	*cd_home(void)
{
	char	*buf;

	buf = malloc(sizeof(char) * 1024);
	buf = getenv("HOME");
	return (buf);
}

int	cd_cmd(char *path)
{
	//struct stat	buffer;

	if (path == NULL)
		path = cd_home();
	// if (stat(path, &buffer) != 0)
	// 	return (0);
	// if(!S_ISDIR(buffer.st_mode))
	// 	return (0);
	if ((access(path, F_OK)== -1) || (access(path, X_OK) == -1) ||
		(access(path, R_OK) == -1) || (access(path, W_OK) == -1))
		return (0);
	if (chdir(path) == -1)
		printf("Error chdir");
}



