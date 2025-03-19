/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:58:25 by irkalini          #+#    #+#             */
/*   Updated: 2025/03/19 21:58:44 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*cd_home(void)
{
	char	*buf;

	buf = malloc(sizeof(char) * 1024);
	buf = getenv("HOME");
	return (buf);
}

void	cd_cmd(char **args)
{
	struct stat	buffer;
	char		*path;

	if (args[2])
	{
		perror("cd");
		return ;
	}
	path = ft_strdup(args[1]);
	if (args[1] == NULL)
		path = cd_home();
	if ((access(path, F_OK)== -1) || (access(path, X_OK) == -1) ||
		(access(path, R_OK) == -1) || (access(path, W_OK) == -1))
		return ;
	if (stat(path, &buffer) != 0)
		return ;
	if(!S_ISDIR(buffer.st_mode))
		return ;
	if (chdir(path) == -1)
		perror("cd");
	//FOR CHECKS
	printf("My function\n");
}
