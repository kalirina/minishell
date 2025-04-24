/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:57:06 by enrmarti          #+#    #+#             */
/*   Updated: 2025/04/24 17:01:54 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*create_shlvl_str(int shlvl)
{
	char	*shlvl_str;
	char	*new_shlvl;

	shlvl_str = ft_itoa(shlvl);
	if (!shlvl_str)
	{
		perror("ft_itoa failed");
		return (NULL);
	}
	new_shlvl = malloc(7 + ft_strlen(shlvl_str) + 1);
	if (!new_shlvl)
	{
		perror("malloc failed");
		free(shlvl_str);
		return (NULL);
	}
	ft_strlcpy(new_shlvl, "SHLVL=", 7);
	ft_strlcpy(new_shlvl + 6, shlvl_str, ft_strlen(shlvl_str) + 1);
	free(shlvl_str);
	return (new_shlvl);
}

void	handle_shlvl(t_shell *shell)
{
	char	*new_shlvl;
	char	*shlvl_value;
	int		i;
	int		shlvl;

	i = 0;
	shlvl = 1;
	while (shell->my_environ[i] != NULL)
	{
		if (ft_strncmp(shell->my_environ[i], "SHLVL=", 6) == 0)
		{
			shlvl_value = shell->my_environ[i] + 6;
			shlvl = ft_atoi(shlvl_value) + 1;
			break ;
		}
		i++;
	}
	new_shlvl = create_shlvl_str(shlvl);
	if (new_shlvl)
	{
		export_add_var(shell, new_shlvl);
		free(new_shlvl);
	}
}
