/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 23:27:53 by irkalini          #+#    #+#             */
/*   Updated: 2025/04/22 17:40:10 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_redir_list(t_redirection *redir)
{
	t_redirection	*next;

	while (redir != NULL)
	{
		next = redir->next;
		free(redir->file);
		free(redir);
		redir = next;
	}
}

void	free_command(t_command *cmd)
{
	int	i;

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
	free_redir_list(cmd->input);
	free_redir_list(cmd->output);
	free(cmd);
}

int	init_shell(t_shell **shell)
{
	*shell = malloc(sizeof(t_shell));
	if (!shell)
		return (perror("malloc"), 1);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	init_environ(*shell);
	(*shell)->exit_status = 0;
	(*shell)->cmd = NULL;
	(*shell)->tokens = NULL;
	(*shell)->skip_cmd = false;
	print_banner();
	return (0);
}

void	cleanup_shell(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->my_environ)
		free_split(shell->my_environ);
	if (shell->cmd)
		cleanup_command_line(shell);
	if (shell->tokens)
		free_tokens(shell->tokens, shell);
	if (shell->line_buffer)
		free(shell->line_buffer);
	rl_clear_history();
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
