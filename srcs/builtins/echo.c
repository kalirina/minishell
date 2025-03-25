/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:20:42 by irkalini          #+#    #+#             */
/*   Updated: 2025/03/25 22:39:25 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*echo_env_var(t_shell *shell, char *var)
{
	int			i;
	char		*value;

	i = 0;
	var++;
	while (shell->my_environ[i])
	{
		if (ft_strncmp(shell->my_environ[i],var,ft_strlen(var)) == 0 &&
			shell->my_environ[i][ft_strlen(var)] == '=')
			value = ft_strdup(shell->my_environ[i] + ft_strlen(var) + 1);
		i++;
	}
	if (!value)
		value = "\n";
	return (value);
}

void echo_cmd(t_shell *shell, char **args)
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
			printf("%s",echo_env_var(shell, args[i]));
		else
			printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (ft_strncmp(args[1],"-n",2) == 0 && ft_strlen(args[1]) == 2)
		return ;
	printf("\n");
}
