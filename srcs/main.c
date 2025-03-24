/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:54:30 by enrmarti          #+#    #+#             */
/*   Updated: 2025/03/24 00:18:24 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int	main(void)
{
	t_shell	*shell;

	//check if argc > 1 ?
	//init_shell(&shell);
	shell = (t_shell *)malloc(sizeof(t_shell));
	setup_signal_handlers();
	while (1)
	{
		readline("minishell>");
		add_history(rl_line_buffer);
		if (ft_strncmp(rl_line_buffer, "exit", 4) == 0)
			return (0);
		lexer(shell, rl_line_buffer);
		parser(shell);
		//execution();
		//free_all();
	}
	return (0);
}
