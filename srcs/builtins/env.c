/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 23:59:02 by irkalini          #+#    #+#             */
/*   Updated: 2025/03/14 11:38:20 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	env_cmd(void)
{
	extern char	**environ;
	int			i;

	i = 0;
	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
}
