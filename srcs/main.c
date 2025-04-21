/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:54:30 by enrmarti          #+#    #+#             */
/*   Updated: 2025/04/21 20:34:06 by enrmarti         ###   ########.fr       */
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

void	init_shell(t_shell **shell)
{
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
	int		exit_status;

	exit_status = 0;
	init_shell(&shell);
	while (1)
	{
		shell->line_buffer = readline("minishell>");
		check_line(shell, &exit_status);
		if (skip(shell->line_buffer) || slash(shell->line_buffer))
			continue ;
		if (lexer(shell, rl_line_buffer) == 0 && parser(shell) == 0)
		{
			// print_command(shell->cmd);
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
