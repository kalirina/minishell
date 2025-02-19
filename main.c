/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:54:30 by enrmarti          #+#    #+#             */
/*   Updated: 2025/02/19 19:03:07 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>


char	**ft_split(char const *s, char c);


int	main(void)
{
	char	**output;
	char	*rl;
	int i;

	while (1)
	{
		i = 0;
		readline("minishell>");
		add_history(rl_line_buffer);
		if (strcmp(rl_line_buffer, "q") == 0)
		{
			rl_clear_history();
			free(rl_line_buffer);
			return (0);
		}
		output = ft_split(rl_line_buffer, '|');
		while (output[i])	
			printf("%s\n", output[i++]);
		// rl_redisplay();
	}
	return (0);
}
