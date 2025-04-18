/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 09:31:44 by enrmarti          #+#    #+#             */
/*   Updated: 2025/04/18 09:49:00 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


bool	check_shlv_flag(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "SECRET_F=", 9) == 0)
			return (1);
		i++;
	}
	return (0);
}

char	**add_shlv_flag(char **env)
{
	char	**new;
	int		i;

	i = 0;
	while (env[i])
		i++;
	new = malloc(sizeof(char *) * i + 1);
	if (!new)
		return (NULL);
	
}