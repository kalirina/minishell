/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:54:30 by enrmarti          #+#    #+#             */
/*   Updated: 2025/02/21 17:40:10 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		if (strcmp(rl_line_buffer, "exit") == 0)
		{
			rl_clear_history();
			free(rl_line_buffer);
			rl_line_buffer = NULL;
			return (0);
		}
		start_parse(rl_line_buffer);
		// ft_split, tree of params, building structures, 
		
		execution();
		// forks, pipes, execve, builtins
	}
	return (0);
}
