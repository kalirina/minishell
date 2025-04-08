#include "../includes/minishell.h"

void	print_tokens(t_token *t)
{
	int	i  = 0;
	printf("\nTOKENS:\n");
	while (t)
	{
		printf("[%d]{%c}%s\n", i, t->quotes, t->str);
		i++;
		t = t->next;
	}
}

void	print_red(t_redirection *r)
{
	if (!r)
		printf("\n");
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
	printf("\n\nCOMMANDS STRUCTURES:\n\n");
	while (c)
	{
		i = 0;
		printf("-----------------------\n\n");
		printf("\tARGS\n");
		while (c->args[i])
		{
			printf("[%d]%s\n", i, c->args[i]);
			i++;
		}
		printf("\n");
		printf("\tINPUT\n");
		print_red(c->input);
		printf("\tOUTPUT\n");
		print_red(c->output);
		c = c->next;
	}
	printf("-----------------------\n");
}
