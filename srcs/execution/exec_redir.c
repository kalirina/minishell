/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:31:23 by enrmarti          #+#    #+#             */
/*   Updated: 2025/04/24 23:33:13 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	setup_input_redirections(t_command *cmd)
{
	t_redirection	*input_redir;
	int				fd;

	input_redir = cmd->input;
	while (input_redir != NULL)
	{
		if (input_redir->heredoc)
			fd = input_redir->fd_heredoc;
		else
			fd = safe_open(input_redir->file);
		if (fd == -1)
			return (-1);
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("error exec: dup2 (input)");
			close(fd);
			return (-1);
		}
		close(fd);
		input_redir = input_redir->next;
	}
	return (0);
}

int	setup_output_redirections(t_command *cmd)
{
	t_redirection	*output_redir;
	int				fd;
	int				flags;

	output_redir = cmd->output;
	while (output_redir != NULL)
	{
		flags = O_WRONLY | O_CREAT;
		if (output_redir->append)
			flags |= O_APPEND;
		else
			flags |= O_TRUNC;
		fd = open(output_redir->file, flags, 0644);
		if (fd == -1)
			return (perror("Error exec: open (output)"), -1);
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("Error exec: dup2 (output)");
			close(fd);
			return (-1);
		}
		close(fd);
		output_redir = output_redir->next;
	}
	return (0);
}

// SETS THE STDIN AND STDOUT OF THE COMMAND TO THE CORRECT
// FILE POINTED TO BY THE REDIRECTION LIST
int	init_redir(t_command *current)
{
	int	flag;

	flag = 0;
	if (current->input)
	{
		if (setup_input_redirections(current) == -1)
			flag = -1;
	}
	if (current->output)
	{
		if (setup_output_redirections(current) == -1)
			flag = -1;
	}
	return (flag);
}
