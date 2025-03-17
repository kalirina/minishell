/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:54:30 by enrmarti          #+#    #+#             */
/*   Updated: 2025/03/16 16:04:39 by irkalini         ###   ########.fr       */
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
		args = ft_split(rl_line_buffer, ' '); //while parsing is not finished
		if (ft_strncmp(args[0], "echo", 4) == 0 && ft_strlen(args[0]) == 4)
			echo_cmd(args);
		else if (ft_strncmp(args[0],"env", 3) == 0 && ft_strlen(args[0]) == 3)
			env_cmd();
		else if (ft_strncmp(args[0],"pwd", 3) == 0 && ft_strlen(args[0]) == 3)
			pwd_cmd();
		else if (ft_strncmp(args[0],"cd", 2) == 0 && ft_strlen(args[0]) == 2)
			cd_cmd(args[1]);
		// else
		// 	execve();
		//free_all();
	}
	return (0);
}
