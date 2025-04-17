/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:03:24 by enrmarti          #+#    #+#             */
/*   Updated: 2025/04/17 17:38:14 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_split(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_fds(int **fds, int n_cmds)
{
	int	i;

	if (!fds || n_cmds <= 1)
		return ;
	i = 0;
	while (i < n_cmds - 1)
	{
		free(fds[i]);
		i++;
	}
	free(fds);
}

void	free_pipe(t_pipe *p, int n_cmds, bool to_close, int j)
{
	int	i;

	if (!p)
		return ;
	if (to_close)
	{
		i = 0;
		while (i < j)
		{
			close(p->fds[i][0]);
			close(p->fds[i][1]);
		}
	}
	if (p->fds)
		free_fds(p->fds, n_cmds);
	if (p->pids)
		free(p->pids);
	free(p);
}

void	free_executer(t_executer *e, bool to_close)
{
	free_pipe(e->pipe, e->n_cmds, to_close, e->n_cmds -1);
	free(e);
}

void	reset_stdinout(t_executer *ex)
{
	dup2(ex->saved_stdin, STDIN_FILENO);
	dup2(ex->saved_stdout, STDOUT_FILENO);
	close(ex->saved_stdin);
	close(ex->saved_stdout);
	free(ex);
}
