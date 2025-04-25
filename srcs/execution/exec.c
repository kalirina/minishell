/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 22:31:02 by irkalini          #+#    #+#             */
/*   Updated: 2025/04/25 16:31:59 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

volatile sig_atomic_t	g_heredoc_interrupt = 0;

int	execute_builtin_cmd(t_shell *shell, char **args, t_executer *ex)
{
	int	status;

	status = 1;
	if (check_builtin_name(args[0], "echo"))
		status = echo_cmd(args);
	else if (check_builtin_name(args[0], "cd"))
		status = cd_cmd(shell);
	else if (check_builtin_name(args[0], "pwd"))
		status = pwd_cmd(args);
	else if (check_builtin_name(args[0], "export"))
		status = export_cmd(shell, args);
	else if (check_builtin_name(args[0], "unset"))
		status = unset_cmd(shell, args);
	else if (check_builtin_name(args[0], "env"))
		status = env_cmd(shell);
	else if (check_builtin_name(args[0], "exit"))
		status = exit_cmd(shell, args, ex);
	return (status);
}

void	child_ext_cmd(t_shell *shell, char **args, char *path, t_executer *ex)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	execve(path, args, shell->my_environ);
	print_error(args[0], NULL, strerror(errno));
	free(path);
	if (errno == EACCES)
		ft_exit(shell, 126, ex);
	ft_exit(shell, 127, ex);
}

void	exec_ext_cmd(t_shell *shell, char **args, t_executer *ex)
{
	char	*path;
	pid_t	pid;
	int		status;

	path = get_exec_path(shell, args[0]);
	if (!path)
	{
		if (!shell->skip_cmd)
			shell->exit_status = 127;
		else
			shell->skip_cmd = false;
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		(perror("minishell: fork"), free(path));
		shell->exit_status = 1;
	}
	if (pid == 0)
		child_ext_cmd(shell, args, path, ex);
	(signal(SIGINT, SIG_IGN), waitpid(pid, &status, 0));
	signal(SIGINT, handle_sigint);
	handle_exec_status(shell, status);
	free(path);
}

//EXECUTES A SINGLE COMMAND
void	execute_cmd(t_shell	*shell, t_executer *ex)
{
	t_command	*current;

	current = shell->cmd;
	if (init_redir(current) == -1)
	{
		reset_stdinout(ex);
		return ;
	}
	if (is_builtin(current->args))
		shell->exit_status = execute_builtin_cmd(shell, shell->cmd->args, ex);
	else
		exec_ext_cmd(shell, current->args, ex);
	reset_stdinout(ex);
}

void	execute(t_shell *shell)
{
	t_executer	*ex;

	if (shell->cmd == NULL)
		return ;
	ex = init_executer(shell->cmd);
	if (!ex)
		return ;
	preprocess_heredoc(shell, ex);
	if (g_heredoc_interrupt)
		return ;
	if (ex->n_cmds > 1)
		execute_pipeline(shell, ex);
	else
		execute_cmd(shell, ex);
	free_executer(ex);
}
