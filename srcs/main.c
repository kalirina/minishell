/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:54:30 by enrmarti          #+#    #+#             */
/*   Updated: 2025/04/24 15:13:00 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_shell	*shell;
	int		exit_status;

	((void)argc, (void)argv);
	exit_status = 0;
	init_shell(&shell, env);
	while (1)
	{
		shell->line_buffer = readline(GREEN"min"RES"ish"RED"ell"RES">");
		check_line(shell, &exit_status);
		if (skip(shell->line_buffer) || slash(shell->line_buffer))
			continue ;
		if (lexer(shell, rl_line_buffer) == 0 && parser(shell) == 0)
			execute(shell);
		free_commands(shell);
	}
	exit_status = shell->exit_status;
	cleanup_shell(shell);
	return (exit_status);
}
