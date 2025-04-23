/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 20:45:19 by irkalini          #+#    #+#             */
/*   Updated: 2025/04/23 20:52:25 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	arg_has_slash(const char *arg)
{
	if (!arg)
		return (false);
	while (*arg)
	{
		if (*arg == '/')
			return (true);
		arg++;
	}
	return (false);
}

bool	arg_starts_dot_slash(const char *arg)
{
	if (!arg || !arg[0])
		return (false);
	return (arg[0] == '.' || arg[0] == '/');
}

char	*path_with_cdpath(t_shell *shell, char *arg)
{
	return (NULL);
}
