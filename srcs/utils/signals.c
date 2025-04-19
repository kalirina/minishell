/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:34:54 by enrmarti          #+#    #+#             */
/*   Updated: 2025/04/19 15:32:10 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

volatile sig_atomic_t	g_signal = 0;

void	handle_shell_signal(void)
{
	if (g_signal == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_signal = 0;
	}
	else if (g_signal == SIGQUIT)
		g_signal = 0;
}

void	handle_sigint(int signo)
{
	g_signal = signo;
}

void	handle_sigquit(int signo)
{
	g_signal = signo;
}

void	setup_signal_handlers(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = handle_sigint;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;

	sa_quit.sa_handler = handle_sigquit;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;

	sigaction(SIGINT, &sa_int, NULL);
	sigaction(SIGQUIT, &sa_quit, NULL);
}

// void	handle_sigint(int signo)
// {
// 	(void)signo;
// 	if (g_pid == -1) // Interactive mode (no child running)
// 	{
// 		write(STDOUT_FILENO, "\n", 1);
// 		rl_replace_line("", 0);
// 		rl_on_new_line();
// 		rl_redisplay();
// 	}
// 	else if (g_pid > 0) // Child process is running
// 	{
// 		kill(g_pid, SIGINT); //sigint to child
// 		write(STDOUT_FILENO, "\n", 1);
// 		g_pid = -1;
// 	}
// }

// void	handle_sigquit(int signo)
// {
// 	(void)signo;
// 	if (g_pid > 0) // Child process is running
// 	{
// 		kill(g_pid, SIGQUIT); // Send SIGQUIT to the child
// 	}
// }
