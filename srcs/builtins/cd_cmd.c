/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:58:25 by irkalini          #+#    #+#             */
/*   Updated: 2025/02/21 19:15:53 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"
# include "../libft/libft.h"

int	cd_cmd(char *path)
{
	struct stat	buffer;
	char		*normal_path;

	if (path == NULL)
		return (0);
	normal_path = normalise_path(path);
	if (normal_path == NULL)
		return (0);
	if (stat(path, &buffer) != 0)
		return (0);
	if(!S_ISDIR(buffer.st_mode))
		return (0);
	if (acces(path, X_OK) == -1)
		return (0);
	if (chdir(path) == -1)
		printf("Error chdir");
}

char	*normalise_path(const char *path)
{
	char	**components;
	char	*normal_path;
	int		i;

	components = ft_split(path, '/');
	i = 0;
	while (components[i])
	{
		if (ft_strncmp(components[i], ".", ft_strlen(components[i])))
			i++;
		if (ft_strncmp(components[i], "..", ft_strlen(components[i])))
		return ;
	}
}
