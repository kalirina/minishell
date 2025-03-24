/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:54:30 by enrmarti          #+#    #+#             */
/*   Updated: 2025/03/24 19:15:10 by enrmarti         ###   ########.fr       */
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
	init_environ(shell);
	while (1)
	{
		readline("minishell>");
		add_history(rl_line_buffer);
		if (!rl_line_buffer || skip(rl_line_buffer) || slash(rl_line_buffer))
			continue ;
		lexer(shell, rl_line_buffer);
		parser(shell);
		execute(shell, shell->cmd->args);
		free_split(shell->cmd->args);
	}
	//free_all();
	return (0);
}
