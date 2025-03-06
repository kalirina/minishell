/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:54:30 by enrmarti          #+#    #+#             */
/*   Updated: 2025/03/06 16:11:40 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	t_shell	*shell;
	int i;

	//check if argc > 1 ?
	//init_shell(&shell);
	shell = (t_shell *)malloc(sizeof(t_shell));
	shell->tokens = malloc(sizeof(t_token));
	shell->tokens = NULL;
	while (1)
	{
		i = 0;
		readline("minishell>");
		add_history(rl_line_buffer);
		if (strcmp(rl_line_buffer, "exit") == 0)
			return (0);
		lexer(shell, rl_line_buffer);

		//execution();
	}
	return (0);
}
