/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 23:27:53 by irkalini          #+#    #+#             */
/*   Updated: 2025/04/14 14:12:27 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_command(t_command *cmd)
{
	int				i;
	t_redirection	*current;
	t_redirection	*next;

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

int	init_shell(t_shell **shell)
{
	*shell = malloc(sizeof(t_shell));
	if (!shell)
		return (perror("malloc"), 1);
	signal(SIGINT, &handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	init_environ(*shell);
	(*shell)->nb_pipe = 0;
	(*shell)->nb_cmd = 0;
	(*shell)->exit_status = 0;
	(*shell)->cmd = NULL;
	return (0);
}

void	cleanup_command_line(t_shell *shell)
{
	free_command(shell->cmd);
	shell->cmd = NULL;
}

void	cleanup_shell(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->my_environ != NULL)
		free_split(shell->my_environ);
	if (shell->cmd != NULL)
		cleanup_command_line(shell);
	if (shell->line_buffer != NULL)
		free(shell->line_buffer);
	free(shell);
}

void	check_line(t_shell *shell, int *exit_status)
{
	if (!shell->line_buffer)
	{
		printf("exit\n");
		cleanup_shell(shell);
		rl_clear_history();
		exit(*exit_status);
	}
	if (shell->line_buffer[0] != '\0')
		add_history(shell->line_buffer);
}
