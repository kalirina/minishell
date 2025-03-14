/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:20:42 by irkalini          #+#    #+#             */
/*   Updated: 2025/03/14 12:48:04 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../libft/libft.h"

void echo_cmd(int argc, char **argv)
{
	int	i;

	if (argc == 0)
		return ;
	i = 0;
	if (ft_strncmp(argv[0],"-n",2) == 0)
		i++;
	while (argv[i])
	{
		printf("%s", argv[i]);
		printf(" ");
		i++;
	}
	if (ft_strncmp(argv[0],"-n",2) != 0)
		printf("\n");
}

int main(int argc, char **argv){
	echo_cmd(argc - 1, argv + 1);
	return (0);
}
