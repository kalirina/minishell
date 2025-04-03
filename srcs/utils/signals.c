/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:34:54 by enrmarti          #+#    #+#             */
/*   Updated: 2025/03/20 19:40:20 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int g_signal_received;

static void	signal_handler(int signo)
{
	g_signal_received = signo;
	if (signo == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_post_cmd_signal(t_shell *shell)
{
	if (g_signal_received == SIGINT)
		shell->exit_status = 1;
	g_signal_received = 0;
}

void setup_signal_handlers(void) 
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sa_int.sa_handler = signal_handler;
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
		perror("minishell: sigaction SIGINT failed");
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sa_quit.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
		perror("minishell: sigaction SIGINT failed");
}
