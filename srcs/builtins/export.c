/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 20:44:35 by irkalini          #+#    #+#             */
/*   Updated: 2025/04/24 17:52:58 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_export_line(char *env_line)
{
	char	*val_ptr;

	val_ptr = ft_strchr(env_line, '=');
	if (val_ptr)
	{
		write(1, "declare -x ", 11);
		write(1, env_line, (val_ptr - env_line));
		write(1, "=\"", 2);
		ft_putstr_fd(val_ptr + 1, 1);
		write(1, "\"\n", 2);
	}
	else
	{
		write(1, "declare -x ", 11);
		ft_putstr_fd(env_line, 1);
		write(1, "\n", 1);
	}
}

void	export_no_arg(t_shell *shell)
{
	char	**env_copy;
	int		i;
	int		count;

	count = 0;
	while (shell->my_environ && shell->my_environ[count])
		count++;
	env_copy = malloc(sizeof(char *) * (count + 1));
	if (!env_copy)
		return (perror("minishell: export: malloc failed"));
	i = 0;
	while (i < count)
	{
		env_copy[i] = shell->my_environ[i];
		i++;
	}
	env_copy[count] = NULL;
	sort_env_array(env_copy, count);
	i = 0;
	while (env_copy[i])
	{
		print_export_line(env_copy[i]);
		i++;
	}
	free(env_copy);
}

int	export_add_var(t_shell *shell, char *arg)
{
	char	*var;
	char	*val;
	int		ret;

	var = get_var(arg);
	if (!var)
		return (1);
	if (!is_valid_var(var))
		return (free(var), 1);
	val = get_val(arg);
	if (!val && ft_strchr(arg, '='))
		return (free(var), 1);
	ret = set_env_var(shell, var, val);
	free(var);
	free(val);
	return (ret);
}

int	export_cmd(t_shell *shell, char **args)
{
	int		i;
	int		status;
	char	*tmp;

	status = 0;
	if (!args[1] || check_empty_str(args[1]))
		return (export_no_arg(shell), 0);
	i = 1;
	while (args[i])
	{
		if (export_add_var(shell, args[i]) != 0)
		{
			tmp = get_var(args[i]);
			if (!tmp || !is_valid_var(tmp))
				print_error("export", args[i], "not a valid identifier");
			free(tmp);
			status = 1;
		}
		i++;
	}
	return (status);
}
