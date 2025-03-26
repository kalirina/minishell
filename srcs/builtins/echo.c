/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:20:42 by irkalini          #+#    #+#             */
/*   Updated: 2025/03/26 16:06:00 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*echo_env_var(char *name_var)
{
	extern char	**environ;
	int			i;
	char		*value;

	i = 0;
	name_var++;
	while (environ[i])
	{
		if (ft_strncmp(environ[i],name_var,ft_strlen(name_var)) == 0 &&
			environ[i][ft_strlen(name_var)] == '=')
			value = ft_strdup(environ[i] + ft_strlen(name_var) + 1);
		i++;
	}
	if (!value)
		value = "\n";
	return (value);
}

void echo_cmd(char **args)
{
	int	i;

	if (args[1] == NULL)
	{
		printf("\n");
		return ;
	}
	i = 1;
	if (ft_strncmp(args[i],"-n",2) == 0 && ft_strlen(args[i]) == 2)
		i++;
	while (args[i])
	{
		if (args[i][0] == '$')
			printf("%s",echo_env_var(args[i]));
		else
			printf("%s ", args[i]);
		i++;
	}
	if ((ft_strncmp(args[1],"-n",2) != 0))
		printf("\n");
}
