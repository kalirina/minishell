/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:20:42 by irkalini          #+#    #+#             */
/*   Updated: 2025/03/26 11:12:35 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_empty_variable(char *str)
{
	if (ft_strncmp(str, "$\"\"", 3) == 0 || ft_strncmp(str, "$''", 3) == 0)
		return ;
}

char	*echo_env_val(t_shell *shell, char *var)
{
	int		i;
	char	*value;
	size_t	var_len;

	i = 0;
	var_len = ft_strlen(var);
	value = NULL;
	while (shell->my_environ[i] && !value)
	{
		if (ft_strncmp(shell->my_environ[i], var, var_len) == 0
			&& shell->my_environ[i][var_len] == '=')
			value = ft_strdup(shell->my_environ[i] + var_len + 1);
		i++;
	}
	if (!value)
		value = ft_strdup("");
	return (value);
}

int	handle_variable(t_shell *shell, char *str, int *first_arg)
{
	int		len;
	char	*var_name;
	char	*value;

	len = 1;
	// if (str[1] == '?')
	// 	return (handle_exit_status(shell), 2); //HANDLE
	if (str[1] == '\0') // Handle case where $ is followed by nothing
	{
		if (*first_arg == 0)
			ft_putchar_fd('$', 1);
		return (1);
	}
	while (ft_isalnum(str[len]) || str[len] == '_')
		len++;
	var_name = ft_substr(str, 1, len - 1);
	value = echo_env_val(shell, var_name);
	if (value && value[0] != '\0') // Only print if variable is not empty
	{
		if (*first_arg == 0)
			*first_arg = 1; // Mark first argument processed
		else
			ft_putchar_fd(' ', 1); // Add space between arguments
		ft_putstr_fd(value, 1); // Print the value of the variable
	}
	free(value);
	free(var_name);
	return (len);
}

void	process_echo_arg(t_shell *shell, char *arg, int *first_arg)
{
	int	j;
	int	escaped;

	j = 0;
	escaped = 0;
	while (arg[j])
	{
		if (!escaped && arg[j] == '\\')
			escaped = 1;
		else
		{
			if (arg[j] == '$' && !escaped)
			{
				j += handle_variable(shell, arg + j, first_arg);
				continue ;
			}
			if (*first_arg == 0) // Avoid leading space for first argument
				*first_arg = 1;
			else
				ft_putchar_fd(' ', 1); // Add space between arguments
			ft_putchar_fd(arg[j], 1); // Print regular characters
			escaped = 0;
		}
		j++;
	}
}

int	is_valid_n_flag(char *arg)
{
	int	i;

	if (arg[0] != '-' || arg[1] != 'n')
		return (0);
	i = 2;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void echo_cmd(t_shell *shell, char **args)
{
	int	i;
	int	newline;
	int	first_arg;

	i = 1;
	newline = 1;
	first_arg = 0; // Track if it's the first argument to avoid leading spaces
	while (args[i] && is_valid_n_flag(args[i]))
	{
		newline = 0; // Disable newline printing for valid -n flags
		i++;
	}
	while (args[i])
	{
		process_echo_arg(shell, args[i], &first_arg);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', 1);
}
