/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:54:30 by enrmarti          #+#    #+#             */
/*   Updated: 2025/03/28 17:40:10 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_tokens(t_token *t)
{
	int	i = 0;

	printf("Tokens:\n");
	while (t)
	{
		printf("\t[%d]%s     quotes: %c\n", i, t->str, t->quotes);
		t = t->next;
		i++;
	}
	printf("\n\n");
}

void	print_red(t_redirection	*red)
{
	while (red)
	{
		printf("\t\t%s,  append:%d\n", red->file, red->append);
		red = red->next;
	}
}

void	print_cmd(t_command *cmd)
{
	int	i = 0;

	while (cmd)
	{
		printf("Command:\n");
		printf("\tArgs:\n");
		i = 0;
		while (cmd->args[i])
		{
			printf("\t\t[%d]%s\n", i, cmd->args[i]);
			i++;
		}
		printf("\tInput:\n");
		print_red(cmd->input);
		printf("\tOutput:\n");
		print_red(cmd->output);
		cmd = cmd->next;
	}
}

void	debug(t_shell	*shell)
{
	//print_tokens(shell->tokens);
	print_cmd(shell->cmd);
}


int	main(void)
{
	t_shell	*shell;

	//check if argc > 1 ?
	//init_shell(&shell);
	shell = (t_shell *)malloc(sizeof(t_shell));
	setup_signal_handlers();
	init_environ(shell);
	while (1)
	{
		readline("minishell>");
		add_history(rl_line_buffer);
		if (!rl_line_buffer || skip(rl_line_buffer) || slash(rl_line_buffer))
			continue ;
		lexer(shell, rl_line_buffer);
		parser(shell);
		//debug(shell);
		if (shell->cmd)
		{
			execute(shell, shell->cmd);
			free_split(shell->cmd->args);
			free(shell->tokens);
			shell->tokens = NULL;
			free(shell->cmd);
			shell->cmd = NULL;
		}
	}
	//free_all();
	return (0);
}
