/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:20:42 by irkalini          #+#    #+#             */
/*   Updated: 2025/03/16 15:58:39 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../libft/libft.h"

void echo_cmd(char **args)
{
	int	i;

	if (args[1] == NULL)
	{
		printf("\n");
		return ;
	}
	i = 1;
	if (ft_strncmp(args[i],"-n",2) == 0)
		i++;
	while (args[i])
	{
		printf("%s", args[i]);
		printf(" ");
		i++;
	}
	if ((ft_strncmp(args[1],"-n",2) != 0))
		printf("\n");
}
