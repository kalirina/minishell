/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:33:58 by enrmarti          #+#    #+#             */
/*   Updated: 2025/04/23 12:22:39 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//RUNS THE COMMAND IN A CHILD PROCESS
void	child_process(t_shell *shell, t_executer *ex, t_command *current, int i)
{
	char	*path;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (i > 0)
		dup2(ex->pipe->fds[i - 1][0], STDIN_FILENO);
	if (i < ex->n_cmds - 1)
		dup2(ex->pipe->fds[i][1], STDOUT_FILENO);
	close_all_pipes(ex->pipe, ex->n_cmds);
	if (setup_input_redirections(current))
		ft_exit(shell, EXIT_FAILURE);
	if (setup_output_redirections(current))
		ft_exit(shell, EXIT_FAILURE);
	if (is_builtin(current->args))
		ft_exit(shell, execute_builtin_cmd(shell, current->args));
	else
	{
		path = get_exec_path(shell, current->args[0]);
		if (!path)
			ft_exit(shell, 127);
		execve(path, current->args, shell->my_environ);
		perror("Error exec: execve");
		free(path);
		ft_exit(shell, EXIT_FAILURE);
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
	int			sigint_flag;
	int			sigquit_flag;

	sigint_flag = 0;
	sigquit_flag = 0;
	current = ex->cmds;
	i = 0;
	signal(SIGINT, SIG_IGN);
	while (i < ex->n_cmds)
	{
		execute_fork(shell, ex, current, i);
		current = current->next;
		i++;
	}
	close_all_pipes(ex->pipe, ex->n_cmds);
	handle_wait_signals(ex, &sigint_flag, &sigquit_flag);
	signal(SIGINT, handle_sigint);
	if (sigint_flag)
		write(STDOUT_FILENO, "\n", 1);
	else if (sigquit_flag)
		write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
}

void	handle_wait_signals(t_executer *ex, int *sigi, int *sigq)
{
	int	i;
	int	status;

	i = 0;
	while (i < ex->n_cmds)
	{
		waitpid(ex->pipe->pids[i], &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			*sigi = 1;
		else if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
			*sigq = 1;
		i++;
	}
}
