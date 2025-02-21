/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:54:30 by enrmarti          #+#    #+#             */
/*   Updated: 2025/02/21 16:09:04 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>


char	**ft_split(char const *s, char c);


int	main(void)
{
	char	**output;
	char	*rl;
	int		i;
	int		pid;

	while (1)
	{
		i = 0;
		rl = readline("minishell>");
		add_history(rl);
		if (strcmp(rl, "q") == 0)
		{
			rl_clear_history();
			free(rl);
			return (0);
		}
		
		while (output[i])
			printf("%s\n", output[i++]);

	}
	return (0);
}
