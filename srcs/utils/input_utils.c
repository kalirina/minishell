/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:09:21 by irkalini          #+#    #+#             */
/*   Updated: 2025/03/23 21:49:15 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	skip(char *line)
{
	int	i;

	if (line[0] == '\0' || (line[0] == ':' && line[1] == '\0') ||
		line[0] == '#' || (line[0] == '!' && line[1] == '\0'))
		return (1);
	i = 0;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
			i++;
		else
			return (0);
	}
	return (1);
}

int	slash(char *line)
{
	int	i;

	if (line[0] != '/')
		return (0);
	i = 1;
	while(line[i])
	{
		if (line[i] == '/' || line[i] == '.')
			i++;
		else
			return (0);
	}
	printf("minishell: %s: Is a directory\n", line);
	return (1);
}
