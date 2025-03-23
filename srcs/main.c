/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:54:30 by enrmarti          #+#    #+#             */
/*   Updated: 2025/03/23 22:35:09 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	t_shell	*shell;
	char	**args;

	//check if argc > 1 ?
	//init_shell(&shell);
	shell = (t_shell *)malloc(sizeof(t_shell)); //to put in init_shell
	init_environ(shell);
	while (1)
	{
		readline("minishell>");
		add_history(rl_line_buffer);
		if (!rl_line_buffer || skip(rl_line_buffer) || slash(rl_line_buffer))
			continue ;
		//lexer(shell, rl_line_buffer);
		//parser(shell);
		args = ft_split(rl_line_buffer, ' '); //TO REPLACE WITH PARSER
		execute(shell,args);
		free_split(args);
	}
	//free_all();
	return (0);
}
