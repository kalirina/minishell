/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:54:30 by enrmarti          #+#    #+#             */
/*   Updated: 2025/04/21 18:32:53 by enrmarti         ###   ########.fr       */
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
	shell->my_environ = NULL;
	init_environ(shell);
	shell->exit_status = 0;
	shell->cmd = NULL;
	shell->uid = get_uid();
}

void	cleanup_command_line(t_shell *shell, char *line_buffer)
{
	free(line_buffer);
	//IMPLEMENT
	//free_parsed_command_structure(shell->cmd);
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
		g_signal_received = 0;
		line_buffer = readline("minishell>");
		handle_post_cmd_signal(shell);
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
		if (lexer(shell, rl_line_buffer) == 0 && parser(shell) == 0)
		{
			// print_command(shell->cmd);
			execute(shell);
			free_command(shell->cmd);
			shell->tokens = NULL;
			shell->cmd = NULL;
		}
		free(line_buffer);
	}
	last_status = shell->exit_status;
	cleanup_shell(shell);
	return (last_status);
}
