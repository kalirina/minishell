/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:58:25 by irkalini          #+#    #+#             */
/*   Updated: 2025/02/23 22:29:54 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"
# include "../libft/libft.h"

// int	cd_cmd(char *path)
// {
// 	struct stat	buffer;
// 	char		*normal_path;

// 	if (path == NULL)
// 		return (0);
// 	normal_path = normalise_path(path);
// 	if (normal_path == NULL)
// 		return (0);
// 	if (stat(path, &buffer) != 0)
// 		return (0);
// 	if(!S_ISDIR(buffer.st_mode))
// 		return (0);
// 	if (acces(path, X_OK) == -1)
// 		return (0);
// 	if (chdir(path) == -1)
// 		printf("Error chdir");
// }

char	*normalise_path(const char *path)
{
	char	**components;
	char	*normal_path;
	int		i;

	components = ft_split(path, '/');
	i = 0;
	while (components[i])
	{
		if (ft_strncmp(components[i], ".", ft_strlen(components[i])) == 0)
			free(components[i]);
		else if (ft_strncmp(components[i], "..", ft_strlen(components[i])) == 0)
		{
			if (i > 0)
			{
				free(components[i - 1]);
				free(components[i]);
			}
		}
		i++;
	}
	components[i] = NULL;
	// i = 0;
	// while (components[i])
	// 	printf("%s\n", components[i++]);
	normal_path = join_components(components);
	//free_components(components);
	//return (normal_path);
}

char	*join_components(char **components)
{
	char	*path;
	int		i;
	int		j;
	int		len;

	i = 0;
	len = 0;
	while (components[i])
	{
		j = 0;
		while (components[i][j])
		{
			len++;
			j++;
		}
		i++;
	}
	printf("%d", len);
	// path = malloc(sizeof(char) * (len + 2));
	// i = 0;
	// path[0] = "/"
	// while (components[i])
	// {

	// }
}

int main()
{
	normalise_path("/home/./ded/h/../f");
	return (0);
}

