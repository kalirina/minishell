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

// Signal handler for Ctrl+C (SIGINT)
void handle_sigint(int sig) {
	printf("test\n");

	(void) sig;
}

// Signal handler for Ctrl+\ (SIGQUIT)
void handle_sigquit(int sig) {

	(void) sig;
}

void setup_signal_handlers() {
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
}
