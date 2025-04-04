/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:55:50 by enrmarti          #+#    #+#             */
/*   Updated: 2025/04/04 14:11:18 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include "../srcs/libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>
# include <limits.h>
# include <fcntl.h>

extern volatile sig_atomic_t	g_signal_received;

typedef struct s_token
{
	char			*str;
	struct s_token	*next;
	char			quotes;
} t_token;

typedef struct s_redirection {
	char					*file;
	bool					append;
	struct s_redirection	*next;
} t_redirection;

typedef struct s_command {
	char				**args;
	t_redirection		*input;
	t_redirection		*output;
	struct s_command	*next;
}	t_command;

typedef struct s_shell
{
	t_token				*tokens;
	t_command			*cmd;
	char				**my_environ;
	int					exit_status;
}	t_shell;

void	lexer(t_shell *shell, char *line);
void	expand(t_shell	*shell);
void	parser(t_shell *shell);

//parsing utils
char	*skip_spaces(char *str);
bool	is_space(char str);
char	*ft_strndup(const char *s, size_t n);
t_redirection *add_redirection(t_redirection **head, char *file, bool append);
void	free_command(t_command *cmd);


t_token	*create_token(char *str);
t_token	*add_token(t_token **head, t_token *new);
t_token	*get_last_token(t_token **head);
t_token	*clean_tokens(t_token *tokens);

//test
void	print_tokens(t_token *t);
int		setup_input_redirections(t_command *cmd);
int		setup_output_redirections(t_command *cmd);
void	setup_signal_handlers(void);
//utils
void	init_environ(t_shell *shell);
int		skip(char *line);
int		slash(char *line);

int		print_error(char *cmd, char *arg, char *msg);
char	*get_env_var_value(char **my_environ, const char *var_name);
int		find_env_var_index(char **my_environ, const char *var);
int		set_env_var(t_shell *shell, char *var, char *val);
void	handle_post_cmd_signal(t_shell *shell);

char	*get_var(char *arg);
char	*get_val(char *arg);
void	add_new_env_var(t_shell *shell, int i, char *var, char *val);
void	update_env_var(t_shell *shell, int i, char *var, char *val);
char	*cd_get_oldpwd_target(t_shell *shell);
char	*cd_get_home_target(t_shell *shell);
void	sort_env_array(char **array, int count);
void	cleanup_shell(t_shell *shell);
void	cleanup_command_line(t_shell *shell, char *line_buffer);
//execution
void	execute(t_shell *shell);
void	free_split(char **tab);
int		is_builtin(char **args);
int		is_valid_var(char *name);
int		check_builtin_name(const char *arg0, const char *builtin_name);
//builtins
int		echo_cmd(t_shell *shell);
int		env_cmd(t_shell *shell);
int		pwd_cmd(void);
int		exit_cmd(t_shell *shell, char **args);
int		cd_cmd(t_shell *shell);
int		export_cmd(t_shell *shell, char **args);
int		unset_cmd(t_shell *shell, char **args);

#endif
