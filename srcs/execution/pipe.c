/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:33:58 by enrmarti          #+#    #+#             */
/*   Updated: 2025/04/19 15:39:23 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//RUNS THE COMMAND IN A CHILD PROCESS
void	child_process(t_shell *shell, t_executer *ex, t_command *current, int i)
{
	char	*path;

	// signal(SIGINT, SIG_DFL);
	// signal(SIGQUIT, SIG_DFL);
	if (i > 0)
		dup2(ex->pipe->fds[i - 1][0], STDIN_FILENO);
	if (i < ex->n_cmds - 1)
		dup2(ex->pipe->fds[i][1], STDOUT_FILENO);
	close_all_pipes(ex->pipe, ex->n_cmds);
	if (setup_input_redirections(current))
		exit(EXIT_FAILURE);
	if (setup_output_redirections(current))
		exit(EXIT_FAILURE);
	if (is_builtin(current->args))
		exit(execute_builtin_cmd(shell, current->args));
	else
	{
		path = get_exec_path(shell, current->args[0]);
		if (!path)
			exit(127);
		execve(path, current->args, shell->my_environ);
		perror("Error exec: execve");
		free(path);
		exit(EXIT_FAILURE);
	}
}

//FORKS THE PROCESS (ITS CALLED FOR EVERY CMD)
void	execute_fork(t_shell *shell, t_executer *ex, t_command *current, int i)
{
	t_pipe	*pipe;

	pipe = ex->pipe;
	pipe->pids[i] = fork();
	if (pipe->pids[i] == -1)
	{
		(perror("Error exec: fork"), free_executer(ex, 1));
		return ;
	}
	if (pipe->pids[i] == 0)
		child_process(shell, ex, current, i);
}

//MAINLY HANDLES THE EXECUTION OF THE PIPELINE
void	execute_pipeline(t_shell *shell, t_executer *ex)
{
	t_command	*current;
	int			i;
	struct sigaction	sa_ignore;

	// Ignore signals in parent during pipeline
	sa_ignore.sa_handler = SIG_IGN;
	sigemptyset(&sa_ignore.sa_mask);
	sa_ignore.sa_flags = 0;
	sigaction(SIGINT, &sa_ignore, NULL);
	sigaction(SIGQUIT, &sa_ignore, NULL);

	current = ex->cmds;
	i = 0;
	while (i < ex->n_cmds)
	{
		execute_fork(shell, ex, current, i);
		current = current->next;
		i++;
	}
	close_all_pipes(ex->pipe, ex->n_cmds);
	i = 0;
	while (i < ex->n_cmds)
		waitpid(ex->pipe->pids[i++], NULL, 0);

	setup_signal_handlers();
}
