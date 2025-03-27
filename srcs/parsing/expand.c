/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:20:15 by enrmarti          #+#    #+#             */
/*   Updated: 2025/03/27 13:45:19 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
			break ;
		i++;
	}
	return (value);
}

char	*handle_variable(t_shell *shell, char *arg)
{
	char	*var_name;
	char	*value;
	int		len;

	len = 1;

	// Handle $? -> exit status
	if (arg[1] == '?')
		return (ft_itoa(shell->exit_status));

	// Handle $ -> literal $
	if (arg[1] == '\0')
		return (ft_strdup("$"));

	// Handle $9HOME -> HOME (skip one digit after $)
	if (ft_isdigit(arg[1]))
		return (ft_substr(arg, 2, ft_strlen(arg) - 2));

	// Handle $=HOME -> literal $=HOME
	if (arg[1] == '=')
		return (ft_strdup(arg));

	// Handle regular variables ($VAR_NAME)
	while (ft_isalnum(arg[len]) || arg[len] == '_')
		len++;
	var_name = ft_substr(arg, 1, len - 1); // Extract variable name
	value = echo_env_val(shell, var_name); // Get variable value from environment
	free(var_name);

	if (!value)
		return (ft_strdup("")); // Return empty string if variable not found

	return (value); // Return expanded value
}


void	expand(t_shell *shell)
{
	if (!shell->tokens)
		return (NULL);

}
