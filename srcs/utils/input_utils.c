/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:09:21 by irkalini          #+#    #+#             */
/*   Updated: 2025/03/27 03:25:49 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	skip(char *line)
{
	int	i;

	if (line[0] == '\0' || (line[0] == ':' && line[1] == '\0')
		|| line[0] == '#' || (line[0] == '!' && line[1] == '\0'))
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
	while (line[i])
	{
		if (line[i] == '/' || line[i] == '.')
			i++;
		else
			return (0);
	}
	printf("minishell: %s: Is a directory\n", line);
	return (1);
}

int	print_error(char *cmd, char *arg, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	if (arg)
	{
		ft_putstr_fd("`", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': ", 2);
	}
	ft_putstr_fd(msg, 2);
	ft_putchar_fd('\n', 2);
	return (1);
}

static char	*cd_get_target(t_shell *shell, char **args)
{
	char	*target_path;

	if (args[1] == NULL || ft_strncmp(args[1], "~", 2) == 0)
	{
		target_path = cd_get_home_target(shell);
	}
	else if (ft_strncmp(args[1], "-", 2) == 0)
	{
		target_path = cd_get_oldpwd_target(shell);
	}
	else
	{
		target_path = ft_strdup(args[1]);
		if (!target_path)
			perror("minishell: cd: ft_strdup failed");
	}
	return (target_path);
}
