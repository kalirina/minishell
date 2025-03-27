/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:54:30 by enrmarti          #+#    #+#             */
/*   Updated: 2025/03/27 20:01:00 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_shell(t_shell *shell)
{
	setup_signal_handlers();
	init_environ(shell);
	shell->exit_status = 0;
	shell->cmd = NULL;
}

void	cleanup_command_line(t_shell *shell, char *line_buffer)
{
	free(line_buffer);
	// Free the structure(s) created by the parser for this line
	// This function depends heavily on how your parser allocates memory.
	// It might involve freeing a list of t_cmd, including args, redirs etc.
	// free_parsed_command_structure(shell->cmd); //IMPLEMENT + free_split(shell->cmd->args);
	shell->cmd = NULL;
}

void	cleanup_shell(t_shell *shell)
{
	if (!shell)
		return;
	free_split(shell->my_environ);
	rl_clear_history();
	free(shell);
}

int	main(void)
{
	t_shell	*shell;
	char	*line_buffer;
	int		last_status;

	shell = (t_shell *)malloc(sizeof(t_shell));
	if (!shell)
		perror("malloc");
	init_shell(shell);
	while (1)
	{
		line_buffer = readline("minishell>");
		if (!line_buffer) // (Ctrl+D)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			break ;
		}
		if (line_buffer[0] != '\0')
			add_history(rl_line_buffer);
		if (line_buffer[0] == '\0' || skip(rl_line_buffer)
			|| slash(rl_line_buffer))
		{
			free(line_buffer);
			continue ;
		}
		// if (lexer(shell, line_buffer) == 0 && parser(shell) == 0)//!!!!!would be easier to controll the succes of the process if it was int
		// 	execute(shell);
		lexer(shell, rl_line_buffer);
		parser(shell);
		execute(shell);
		cleanup_command_line(shell, line_buffer);
	}
	cleanup_shell(shell);
	last_status = shell->exit_status;
	return (last_status);
}
