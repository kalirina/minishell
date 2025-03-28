/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:54:30 by enrmarti          #+#    #+#             */
/*   Updated: 2025/03/28 20:18:13 by irkalini         ###   ########.fr       */
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
	clear_history();
	free(shell);
}

int setup_input_redirections(t_command *cmd)
{
	t_redirection *input_redir = cmd->input;
	int fd;

	while (input_redir != NULL) {
		fd = open(input_redir->file, O_RDONLY);
		if (fd == -1) {
			perror("open (input)");
			return -1;  // Indicate error
		}

		if (dup2(fd, STDIN_FILENO) == -1) {
			perror("dup2 (input)");
			close(fd);
			return -1;
		}

		close(fd);  // Close the original file descriptor
		input_redir = input_redir->next;
	}
	return 0; //Success
}

int setup_output_redirections(t_command *cmd) {
	t_redirection *output_redir = cmd->output;
	int fd;
	int flags;

	while (output_redir != NULL) {
		flags = O_WRONLY | O_CREAT;
		if (output_redir->append) {
			flags |= O_APPEND;
		} else {
			flags |= O_TRUNC;
		}

		fd = open(output_redir->file, flags, 0644);
		if (fd == -1) {
			perror("open (output)");
			return -1;
		}

		if (dup2(fd, STDOUT_FILENO) == -1) {
			perror("dup2 (output)");
			close(fd);
			return -1;
		}

		close(fd);
		output_redir = output_redir->next;
	}
	return 0;
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
		if (shell->cmd)
		{
			execute(shell);
			free_split(shell->cmd->args);
			free(shell->tokens);
			shell->tokens = NULL;
			free(shell->cmd);
			shell->cmd = NULL;
		}
	}
	cleanup_shell(shell);
	last_status = shell->exit_status;
	return (last_status);
}
