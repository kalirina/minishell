/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:54:30 by enrmarti          #+#    #+#             */
/*   Updated: 2025/03/14 13:45:29 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	t_shell	*shell;
	char	**args;

	//check if argc > 1 ?
	//init_shell(&shell);
	shell = (t_shell *)malloc(sizeof(t_shell));
	while (1)
	{
		readline("minishell>");
		add_history(rl_line_buffer);
		if (ft_strncmp(rl_line_buffer, "exit", 4) == 0)
			return (0);
		//lexer(shell, rl_line_buffer);
		//parser(shell);
		//execution();
		args = ft_split(rl_line_buffer, ' ');
		if (ft_strncmp(args[0], "echo", 4) == 0)
			echo_cmd(args);
		else if (ft_strncmp(args[0],"env", 3) == 0)
			env_cmd();
		else if (ft_strncmp(args[0],"pwd", 3) == 0)
			pwd_cmd();
		//free_all();
	}
	return (0);
}
