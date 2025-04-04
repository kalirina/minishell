#include "../includes/minishell.h"

void	print_tokens(t_token *t)
{
	int	i  = 0;
	printf("Tokens:\n\n");
	while (t)
	{
		printf("[%d]{%d}%s\n", i, t->quotes, t->str);
		i++;
		t = t->next;
	}
}

void	print_red(t_redirection *r)
{
	while (r)
	{
		printf("file:%s\n", r->file);
		printf("[append %d] [heredoc %d]\n", r->append, r->heredoc);
		r =  r->next;
	}
}

void	print_command(t_command *c)
{
	int i;
	printf("COMMANDS:\n\n");
	while (c)
	{
		i = 0;
		printf("\t\tARGS\n");
		while (c->args[i])
			printf("%s\n", c->args[i++]);
		printf("\t\tINPUT\n");
		print_red(c->input);
		printf("\t\tOUTPUT\n");
		print_red(c->output);
		c = c->next;
	}
}
