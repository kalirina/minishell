/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 20:45:19 by irkalini          #+#    #+#             */
/*   Updated: 2025/04/24 00:18:39 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*path_with_cdpath(t_shell *shell, char *arg)
{
	char	*cdpath_env;
	char	**cdpaths;
	char	*res_path;
	int		i;

	cdpath_env = get_env_var_value(shell->my_environ, "CDPATH");
	if (!cdpath_env)
		return (NULL);
	if (*cdpath_env == '\0')
		return (free(cdpath_env), NULL);
	cdpaths = ft_split(cdpath_env, ':');
	free(cdpath_env);
	if (!cdpaths)
		return (perror("minishell: ft_split failed"), NULL);
	i = 0;
	res_path = NULL;
	while (cdpaths[i])
	{
		res_path = check_cdpath_entry(cdpaths[i], arg, cdpaths);
		if (res_path)
			return (res_path);
		i++;
	}
	return (free_split(cdpaths), NULL);
}

char	*check_cdpath_entry(const char *dir, const char *arg, char **cdpaths)
{
	char	*full_path;

	full_path = ft_strjoin(dir, arg);
	if (!full_path)
		return (perror("minishell: malloc failed"), NULL);
	if (access(full_path, F_OK) == 0)
		return (free_split(cdpaths), full_path);
	free(full_path);
	return (NULL);
}
