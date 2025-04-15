/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:33:58 by enrmarti          #+#    #+#             */
/*   Updated: 2025/04/15 17:54:29 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	create_pipeline_pipes(t_executer *ex, int pipefds[][2])
{
	int	i;

	i = 0;
	while (i < ex->n_commands - 1)
	{
		if (pipe(pipefds[i]) == -1)
			return (perror("error exec : pipe"), -1);
		i++;
	}
	return (0);
}

void	execute_fork(t_shell *shell, pid_t pids[], int pipefds[][2])
{
	
}

void	execute_pipeline(t_shell *shell, t_executer *ex)
{
	t_command	*current;
	pid_t		pids[ex->n_commands];
	int			pipefds[ex->n_commands - 1][2];
	int			i;
	int			j;

	if (create_pipeline_pipes(ex, pipefds) == -1)
		return ;
	i = 0;
	current = ex->cmds;
	while (i < ex->n_commands)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pids[i] == 0)
		{
			if (i > 0)
				dup2(pipefds[i - 1][0], STDIN_FILENO);
			if (i < ex->n_commands - 1)
				dup2(pipefds[i][1], STDOUT_FILENO);
			j = 0;
			while (j < ex->n_commands - 1)
			{
				close(pipefds[j][0]);
				close(pipefds[j++][1]);
			}
			if (setup_input_redirections(current))
				exit(EXIT_FAILURE);
			if (setup_output_redirections(current))
				exit(EXIT_FAILURE);
			if (is_builtin(current->args))
				exit(execute_builtin_cmd(shell, current->args));
			else
			{
				char *path = get_exec_path(shell, current->args[0]);
				if (!path)
					exit(127);
				execve(path, current->args, shell->my_environ);
				perror("execve");
				exit(EXIT_FAILURE);
			}
		}
		current = current->next;
		i++;
	}
	i = 0;
	while (i < ex->n_commands - 1)
	{
		close(pipefds[i][0]);
		close(pipefds[i++][1]);
	}
	i = 0;
	while (i < ex->n_commands)
		waitpid(pids[i++], NULL, 0);
}

// SETS THE STDIN AND STDOUT OF THE COMMAND TO THE CORRECT 
// SPOT IN THE PIPELINE (CALLED ONLY IF ex->pipe == true)
void	pipe_redir(t_executer *ex)
{
	if (ex->pipe_in_fd != -1)
	{
		dup2(ex->pipe_in_fd, STDIN_FILENO);
		close(ex->pipe_in_fd);
	}
	if (ex->pipe_out_fd != -1)
	{
		dup2(ex->pipe_out_fd, STDOUT_FILENO);
		close(ex->pipe_out_fd);
	}
}