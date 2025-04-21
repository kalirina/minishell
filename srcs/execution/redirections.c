/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 23:21:50 by irkalini          #+#    #+#             */
/*   Updated: 2025/04/09 23:24:07 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int setup_input_redirections(t_command *cmd)
{
	t_redirection *input_redir;
	int fd;
	char *heredoc_content;

	input_redir = cmd->input;
	while (input_redir != NULL)
	{
		if (input_redir->heredoc)
		{
			heredoc_content = get_heredoc_input(input_redir->file);
			if (heredoc_content == NULL)
				return (-1);
			fd = open(".temp_heredoc", O_CREAT | O_TRUNC | O_WRONLY, 0600);
			if (fd == -1)
				return (perror("open (input)"), -1);
			write(fd, heredoc_content, strlen(heredoc_content));
			close(fd);
			free(heredoc_content);
			fd = open(".temp_heredoc", O_RDONLY);
			unlink(".temp_heredoc");
		}
		else
			fd = open(input_redir->file, O_RDONLY);
		if (fd == -1)
			return (perror("open (input)"), -1);
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
			return (perror("open (output)"), -1);
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("dup2 (output)");
			close(fd);
			return (-1);
		}
		close(fd);
		output_redir = output_redir->next;
	}
	return (0);
}
