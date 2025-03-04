/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:54:30 by enrmarti          #+#    #+#             */
/*   Updated: 2025/03/04 13:50:06 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_split(char const *s, char c);

int	main(void)
{
	t_shell	shell;
	int i;

	//check if argc > 1 ?
	//init_shell(&shell);
	while (1)
	{
		i = 0;
		readline("minishell>");
		add_history(rl_line_buffer);
		if (strcmp(rl_line_buffer, "exit") == 0)
			return (0);
		process_input(&shell, rl_line_buffer); 
		
		//execution();
	}
	return (0);
}
