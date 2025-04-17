/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:36:30 by enrmarti          #+#    #+#             */
/*   Updated: 2025/04/17 18:48:30 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//CLOSES ALL PIPES
void	close_all_pipes(t_pipe *p, int n_cmd)
{
	int	i;

	i = 0;
	while (i < n_cmd - 1)
	{
		close(p->fds[i][0]);
		close(p->fds[i++][1]);
	}
}

//INITIALISES THE ARRAY OF FD FOR THE PIPELINE
int	**init_pipes_fds(int n_cmds, t_pipe *p)
{
	int	**fds;
	int	i;
	int	j;

	fds = malloc((n_cmds - 1) * sizeof(int *));
	if (!fds)
	{
		(perror("Error exec : malloc fds"), free(p));
		return (NULL);
	}	
	i = 0;
	while (i < n_cmds - 1)
	{
		fds[i] = malloc(2 * sizeof(int));
		if (!fds[i])
		{
			j = 0;
			while (j < i)
				free(fds[j++]);
			perror("Error exec : malloc fds");
			return (free(fds), free(p), NULL);
		}
		i++;
	}
	return (fds);
}

//INITIALISES THE T_PIPE STRUCT AND CREATES THE PIPELINE pipe()
t_pipe	*init_pipes(int n_cmds)
{
	t_pipe	*p;
	int		i;

	p = malloc(sizeof(t_pipe));
	if (!p)
		return (perror("Error exec : malloc pipe"), NULL);
	p->fds = init_pipes_fds(n_cmds, p);
	p->pids = malloc(n_cmds * sizeof(pid_t));
	if (!p->pids)
	{
		free_fds(p->fds, n_cmds);
		(perror("Error exec : malloc pids"), free(p));
		return (NULL);
	}
	i = 0;
	while (i < n_cmds - 1)
	{
		if (pipe(p->fds[i++]) == -1)
		{
			perror("Error exec : pipe");
			free_pipe(p, n_cmds, true, i - 2);
			return (NULL);
		}
	}
	return (p);
}
