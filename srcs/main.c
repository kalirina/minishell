/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:54:30 by enrmarti          #+#    #+#             */
/*   Updated: 2025/03/20 09:19:42 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	t_shell	*shell;
	char	**args;
	int		pid;
	int		status;

	//check if argc > 1 ?
	//init_shell(&shell);
	//to put in init_shell:
	shell = (t_shell *)malloc(sizeof(t_shell));
	init_environ(shell);

	while (1)
	{
		readline("minishell>");
		add_history(rl_line_buffer);
		//lexer(shell, rl_line_buffer);
		//parser(shell);
		args = ft_split(rl_line_buffer, ' '); //TO REPLACE WITH PARSER
		execute(shell,args);
		//free_all();
	}
	return (0);
}
