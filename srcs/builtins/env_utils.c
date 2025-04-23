/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 00:16:19 by irkalini          #+#    #+#             */
/*   Updated: 2025/04/23 16:08:55 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*create_env_string(const char *var, const char *val)
{
	char	*result;
	char	*tmp;

	if (!var)
		return (NULL);
	if (val)
	{
		result = ft_strjoin(var, "=");
		if (!result)
			return (perror("minishell: malloc failed"), NULL);
		tmp = result;
		result = ft_strjoin(result, val);
		if (!result)
			return (perror("minishell: malloc failed"), NULL);
		free(tmp);
		return (result);
	}
	else
	{
		result = ft_strdup(var);
		if (!result)
			return (perror("minishell: malloc failed"), NULL);
		return (result);
	}
}

int	add_env_var(t_shell *shell, char *var, char *val)
{
	int		len;
	char	**new_environ;
	char	*new_entry;

	len = 0;
	while (shell->my_environ[len])
		len++;
	new_entry = create_env_string(var, val);
	if (!new_entry)
		return (perror("minishell: malloc failed"), 1);
	new_environ = malloc(sizeof(char *) * (len + 2));
	if (!new_environ)
		return (perror("minishell: malloc failed"), free(new_entry), 1);
	if (len > 0)
		ft_memcpy(new_environ, shell->my_environ, len * sizeof(char *));
	new_environ[len] = new_entry;
	new_environ[len + 1] = NULL;
	free(shell->my_environ);
	shell->my_environ = new_environ;
	return (0);
}

int	set_env_var(t_shell *shell, char *var, char *val)
{
	int		index;
	char	*new_entry;

	index = find_env_var_index(shell->my_environ, var);
	if (index != -1)
	{
		new_entry = create_env_string(var, val);
		if (!new_entry)
			return (perror("minishell: malloc failed"), 1);
		free(shell->my_environ[index]);
		shell->my_environ[index] = new_entry;
	}
	else
		add_env_var(shell, var, val);
	return (0);
}

int	find_env_var_index(char **my_environ, const char *var)
{
	int		i;
	size_t	len;

	i = 0;
	if (!var)
		return (-1);
	len = ft_strlen(var);
	if (len == 0)
		return (-1);
	while (my_environ && my_environ[i])
	{
		if (ft_strncmp(my_environ[i], var, len) == 0
			&& (my_environ[i][len] == '=' || my_environ[i][len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

char	*get_env_var_value(char **my_environ, const char *var_name)
{
	int		i;
	size_t	len;
	char	*value_start;

	i = find_env_var_index(my_environ, var_name);
	if (i == -1)
		return (NULL);
	len = ft_strlen(var_name);
	if (my_environ[i][len] == '=')
	{
		value_start = my_environ[i] + len + 1;
		return (ft_strdup(value_start));
	}
	return (ft_strdup(""));
}
