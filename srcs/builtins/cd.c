/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:58:25 by irkalini          #+#    #+#             */
/*   Updated: 2025/03/27 14:24:36 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*cd_get_target(t_shell *shell, char **args)
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

char	*cd_get_home_target(t_shell *shell)
{
	char	*env_val;

	env_val = get_env_var_value(shell->my_environ, "HOME");
	if (!env_val)
		return (print_error("cd", NULL, "HOME not set"), NULL);
	if (*env_val == '\0')
		return (free(env_val), print_error("cd", NULL, "HOME not set"), NULL);
	return (env_val);
}

static void	cd_update_env(t_shell *shell, char *old_path)
{
	char	cwd_buf[4097];

	set_env_var(shell, "OLDPWD", old_path);
	free(old_path);
	if (getcwd(cwd_buf, 4096) != NULL)
		set_env_var(shell, "PWD", cwd_buf);
	else
		perror("minishell: cd: error retrieving current directory");
}

static int	cd_check_and_change(char *path)
{
	struct stat	buffer;
	int			chdir_ret;

	if (stat(path, &buffer) != 0)
	{
		print_error("cd", path, strerror(errno));
		return (-1);
	}
	if (!S_ISDIR(buffer.st_mode))
	{
		print_error("cd", path, "Not a directory");
		return (-1);
	}
	chdir_ret = chdir(path);
	if (chdir_ret == -1)
	{
		print_error("cd", path, strerror(errno));
		return (-1);
	}
	return (0);
}

int	cd_cmd(t_shell *shell)
{
	char		*path;
	char		*old_path;
	int			chdir_ret;

	if (shell->cmd->args[1] && shell->cmd->args[2])
		return (print_error("cd", NULL, "too many arguments"));
	old_path = get_env_var_value(shell->my_environ, "PWD");
	path = cd_get_target(shell, shell->cmd->args);
	if (!path)
		return (free(old_path), 1);
	chdir_ret = cd_check_and_change(path);
	if (chdir_ret == -1)
		return (free(path), free(old_path), 1);
	cd_update_env(shell, old_path);
	free(path);
	return (0);
}
