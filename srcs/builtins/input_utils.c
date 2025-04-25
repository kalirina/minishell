/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:09:21 by irkalini          #+#    #+#             */
/*   Updated: 2025/04/25 16:09:13 by irkalini         ###   ########.fr       */
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

int	slash(char *line, t_shell *shell)
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
	printf(RED "minishell: %s: Is a directory\n" RES, line);
	shell->exit_status = 126;
	return (1);
}

int	print_error(char *cmd, char *arg, char *msg)
{
	ft_putstr_fd(RED "minishell: ", 2);
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
	ft_putstr_fd(RES "\n", 2);
	return (1);
}

char	*cd_get_oldpwd_target(t_shell *shell)
{
	char	*env_val;

	env_val = get_env_var_value(shell->my_environ, "OLDPWD");
	if (!env_val)
		return (print_error("cd", NULL, "OLDPWD not set"), NULL);
	if (*env_val == '\0')
		return (free(env_val), print_error("cd", NULL, "OLDPWD not set"), NULL);
	ft_putstr_fd(env_val, 1);
	ft_putchar_fd('\n', 1);
	return (env_val);
}
