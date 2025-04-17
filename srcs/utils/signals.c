/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:34:54 by enrmarti          #+#    #+#             */
/*   Updated: 2025/04/12 18:33:10 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	g_pid = -1;

void	handle_sigint(int signo)
{
	(void)signo;
	if (g_pid == -1) // Interactive mode (no child running)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (g_pid > 0) // Child process is running
	{
		kill(g_pid, SIGINT); //sigint to child
		write(STDOUT_FILENO, "\n", 1);
		g_pid = -1;
	}
}

void	handle_sigquit(int signo)
{
	(void)signo;
	if (g_pid > 0) // Child process is running
	{
		kill(g_pid, SIGQUIT); // Send SIGQUIT to the child
	}
}
