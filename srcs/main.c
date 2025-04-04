/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:54:30 by enrmarti          #+#    #+#             */
/*   Updated: 2025/04/03 19:03:23 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    free_command(t_command *cmd)
{
    int        i;
    t_redirection *current;
    t_redirection *next;

    if (!cmd)
        return ;
    if (cmd->args)
    {
        i = 0;
        while (cmd->args[i] != NULL)
        {
            free(cmd->args[i]);
            i++;
        }
        free(cmd->args);
    }
    current = cmd->input;
    while (current != NULL)
    {
        next = current->next;
        free(current->file);
        free(current);
        current = next;
    }
    current = cmd->output;
    while (current != NULL)
    {
        next = current->next;
        free(current->file);
        free(current);
        current = next;
    }
    free(cmd);
}

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
		lexer(shell, rl_line_buffer);
		//print_tokens(shell->tokens);
		parser(shell);
		//print_command(shell->cmd);
		if (shell->cmd)
		{
			execute(shell);
			free_command(shell->cmd);
			shell->tokens = NULL;
			shell->cmd = NULL;
		}
	}
	cleanup_shell(shell);
	last_status = shell->exit_status;
	return (last_status);
}
