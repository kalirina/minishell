/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:54:30 by enrmarti          #+#    #+#             */
/*   Updated: 2025/03/25 20:31:11 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_shell(t_shell *shell)
{
	setup_signal_handlers();
	init_environ(shell);
}

int	main(void)
{
	t_shell	*shell;

	shell = (t_shell *)malloc(sizeof(t_shell));
	if (!shell)
		perror("malloc");
	init_shell(shell);
	while (1)
	{
		readline("minishell>");
		add_history(rl_line_buffer);
		if (!rl_line_buffer || skip(rl_line_buffer) || slash(rl_line_buffer))
			continue ;
		lexer(shell, rl_line_buffer);
		parser(shell);
		execute(shell);
		free_split(shell->cmd->args);
	}
	//free_all();
	return (0);
}
