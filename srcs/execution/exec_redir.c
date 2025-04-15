/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:31:23 by enrmarti          #+#    #+#             */
/*   Updated: 2025/04/15 17:34:30 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_heredoc(t_redirection *red)
{
	int		fd;
	char	*heredoc_content;

	heredoc_content = get_heredoc_input(red->file);
	if (heredoc_content == NULL)
		return (-1);
	fd = open(".temp_heredoc", O_CREAT | O_TRUNC | O_WRONLY, 0600);
	if (fd == -1)
		return (perror("error exec: open (input)"), -1);
	write(fd, heredoc_content, ft_strlen(heredoc_content));
	close(fd);
	free(heredoc_content);
	fd = open(".temp_heredoc", O_RDONLY);
	unlink(".temp_heredoc");
}

int	setup_input_redirections(t_command *cmd)
{
	t_redirection	*input_redir;
	int				fd;
	char			*heredoc_content;

	input_redir = cmd->input;
	while (input_redir != NULL)
	{
		if (input_redir->heredoc)
		{
			handle_heredoc(input_redir);
		}
		else
			fd = open(input_redir->file, O_RDONLY);
		if (fd == -1)
			return (perror("error exec: open (input)"), -1);
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
			return (perror("error exec: open (output)"), -1);
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("error exec: dup2 (output)");
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
void	init_redir(t_command *current)
{
	int	flg;

	flg = 0;
	if (current->input)
	{
		if (setup_input_redirections(current) == -1)
			flg = 1;
	}
	if (flg == 0 && current->output)
	{
		if (setup_output_redirections(current) == -1)
			flg = 1;
	}
}
