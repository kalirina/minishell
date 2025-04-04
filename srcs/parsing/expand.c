/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:20:15 by enrmarti          #+#    #+#             */
/*   Updated: 2025/04/02 10:44:34 by enrmarti         ###   ########.fr       */
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
		{
			value = ft_strdup(shell->my_environ[i] + var_len + 1);
			break ;
		}
		i++;
	}
	return (value);
}

char	*handle_variable(t_shell *shell, char *arg)
{
	pid_t	pid;
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
		return (ft_strdup("$"));
	// Handle $$
	if (arg[1] == '$')
	{
		pid = getpid();
		return (ft_itoa(pid));
	}
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

char	*extract_var_name(char *arg)
{
	char	*var_name;
	int		len;

	if (arg[1] == '$' || arg[1] == '?')
	{
		var_name = ft_substr(arg, 1, 1);
		return (var_name);
	}
	len = 1;
	while (ft_isalnum(arg[len]) || arg[len] == '_')
		len++;
	var_name = ft_substr(arg, 1, len - 1);
	return (var_name);
}

char	*new_extended_value(char *orig, char *extended, char *start)
{
	char	*res;
	char	*var_name;
	char	*end_of_var;
	int		len;
	int		i;
	int		j;

	var_name = extract_var_name(start);
	end_of_var = start + ft_strlen(var_name) + 1;
	len = ft_strlen(orig) - (ft_strlen(var_name) + 1) + ft_strlen(extended);
	res = malloc(sizeof(char) * len + 1);
	if (!res)
		return (free(var_name), NULL);
	i = 0;
	while (orig < start)
		res[i++] = *orig++;
	j = 0;
	while (extended[j])
		res[i++] = extended[j++];
	while (*end_of_var)
		res[i++] = *end_of_var++;
	res[i] = '\0';
	free(var_name);
	return (res);
}

// void	expand(t_shell *shell)
// {
// 	t_token	*current;
// 	char	*tmp;
// 	char	*extended;
// 	char	*new_value;
// 	char	*last_expansion;

// 	tmp = NULL;
// 	current = shell->tokens;
// 	while (current)
// 	{
// 		last_expansion = NULL;
// 		if (current->quotes == '"' || current->quotes == 0)
// 		{
// 			tmp = ft_strchr(current->str, '$');
// 			while (tmp != NULL)
// 			{
// 				extended = handle_variable(shell, tmp);
// 				new_value = new_extended_value(current->str, extended, tmp);
// 				free(current->str);
// 				free(extended);
// 				current->str = new_value;
// 				printf("new value : %s\n", new_value);
// 				tmp = ft_strchr(current->str, '$');
// 				if (tmp + 1 && tmp)
// 			}
// 		}
// 		current = current->next;
// 	}
// }


void    expand(t_shell *shell)
{
    t_token    *current;
    char    *tmp;
    char    *extended;
    char    *new_value;
    char    *last_expansion_end;

    current = shell->tokens;
    while (current)
    {
        last_expansion_end = NULL; // Initialize
        if (current->quotes == '"' || current->quotes == 0)
        {
            tmp = ft_strchr(current->str, '$');
            while (tmp != NULL)
            {
                // Only expand if this $ is *after* the last expansion
                if (!last_expansion_end || tmp > last_expansion_end)
                {
                    extended = handle_variable(shell, tmp);
                    new_value = new_extended_value(current->str, extended, tmp);
                    free(current->str);
                    free(extended);
                    current->str = new_value;

                    // Update last_expansion_end
                    last_expansion_end = tmp + ft_strlen(new_value); //this line must be reviewd
                    tmp = ft_strchr(current->str, '$');
                }
                else
                {
                    tmp = ft_strchr(tmp + 1, '$');
                }
            }
        }
        current = current->next;
    }
}
