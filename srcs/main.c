/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:54:30 by enrmarti          #+#    #+#             */
/*   Updated: 2025/04/10 01:18:00 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	t_shell	*shell;
	int		exit_status;

	exit_status = 0;
	init_shell(&shell);
	while (1)
	{
		shell->line_buffer = readline("minishell>");
		check_line(shell, &exit_status);
		if (skip(shell->line_buffer) || slash(shell->line_buffer))
			continue ;
		lexer(shell, rl_line_buffer); //if (lexer(shell, line_buffer) == 0 && parser(shell) == 0) => if (shell->cmd) => execute(shell)
		parser(shell);
		if (shell->cmd)
		{
			execute(shell);
			free_command(shell->cmd);
			shell->tokens = NULL;
			shell->cmd = NULL;
		}
	}
	exit_status = shell->exit_status;
	cleanup_shell(shell);
	return (exit_status);
}
