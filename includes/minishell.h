/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:55:50 by enrmarti          #+#    #+#             */
/*   Updated: 2025/04/23 13:12:33 by enrmarti         ###   ########.fr       */
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
# include <fcntl.h>
# include <limits.h>
# include <fcntl.h>

typedef struct s_token
{
	char			*str;
	struct s_token	*next;
}	t_token;

typedef struct s_expansion
{
	char	*token;
	char	*res;
	bool	in_single_quote;
	bool	in_double_quote;
	int		i;
	int		len;
}	t_expansion;

typedef struct s_redirection
{
	char					*file;
	bool					append;
	bool					heredoc;
	int						fd_heredoc;
	struct s_redirection	*next;
}	t_redirection;

typedef struct s_command
{
	char				**args;
	t_redirection		*input;
	t_redirection		*output;
	struct s_command	*next;
}	t_command;

typedef struct s_pipe
{
	pid_t	*pids;
	int		**fds;
}	t_pipe;

typedef struct s_executer
{
	t_command	*cmds;
	int			saved_stdin;
	int			saved_stdout;
	int			n_cmds;
	t_pipe		*pipe;
}	t_executer;

typedef struct s_shell
{
	t_token				*tokens;
	t_command			*cmd;
	char				**my_environ;
	int					exit_status;
	int					uid;
	bool				skip_cmd;
	char				*line_buffer;
}	t_shell;

# define RES		"\033[0m"
# define RED		"\033[0;31m"
# define GREEN		"\033[0;32m"

//parsing
int				lexer(t_shell	*shell, char *line);
int				expand(t_shell *shell);
int				parser(t_shell *shell);
//parsing utils
t_redirection	*add_redirection(
					t_redirection **head,
					char *file,
					bool append,
					bool heredoc);
char			*skip_spaces(char *str);
char			*append_char(char *str, char c);
char			*ft_strndup(const char *s, size_t n);
char			*get_heredoc_input(t_shell *shell, const char *delimiter);
char			*echo_env_val(t_shell *shell, char *var);
bool			is_space(char str);
bool			syntax_check(t_token *t);
bool			check_quotes_inquotes(t_expansion *exp);
bool			check_dollar_quotes(t_expansion *exp);
void			free_command(t_command *cmd);
int				is_redirection_char(char c);
t_expansion		*init_expansion(char *token);
t_command		*new_node(void);
char			*is_redirection(char *str);
t_token			*create_token(char *str);
t_token			*add_token(t_token **head, t_token *new);
void			free_token(t_token *token);
t_redirection	*add_redirection(
					t_redirection **head,
					char *file,
					bool append,
					bool heredoc);
void			free_tokens(t_token *head, t_shell *shell);
//test
void			perform_quote_removal(t_shell *shell);
//signals
void			handle_sigint(int signo);
//utils
int				get_uid(void);
void			handle_shlvl(t_shell *shell);
void			init_environ(t_shell *shell);
int				init_shell(t_shell **shell);
int				skip(char *line);
int				slash(char *line);
char			*new_strjoin(char *s1, char *s2);
void			print_banner(void);
void			ft_exit(t_shell *shell);
//free
void			free_pipe(t_pipe *p, int n_cmds, bool to_close, int j);
void			free_fds(int **fds, int n_cmds);
void			free_executer(t_executer *e);
void			close_all_pipes(t_pipe *p, int n_cmd);
void			free_commands(t_shell *shell);
void			cleanup_shell(t_shell *shell);
void			check_line(t_shell *shell, int *exit_status);
int				print_error(char *cmd, char *arg, char *msg);
//environment
char			*get_env_var_value(char **my_environ, const char *var_name);
int				find_env_var_index(char **my_environ, const char *var);
int				set_env_var(t_shell *shell, char *var, char *val);
char			*get_var(char *arg);
char			*get_val(char *arg);
char			*cd_get_oldpwd_target(t_shell *shell);
char			*cd_get_home_target(t_shell *shell);
void			sort_env_array(char **array, int count);
int				is_valid_var(char *name);
//execution
void			execute(t_shell *shell);
void			execute_pipeline(t_shell *shell, t_executer *ex);
void			preprocess_heredoc(t_shell *shell);
void			exec_ext_cmd(t_shell *shell, char **args);
void			free_split(char **tab);
int				is_builtin(char **args);
char			*get_exec_path(t_shell *shell, char *cmd);
char			*find_cmd_in_path(t_shell *shell, char *cmd);
void			handle_exec_status(t_shell *shell, int status);
void			handle_wait_signals(t_executer *ex, int *sigi, int *sigq);
char			*check_path_entry(
					const char *dir,
					const char *cmd,
					char **paths);
int				check_builtin_name(const char *arg0, const char *builtin_name);
int				execute_builtin_cmd(t_shell *shell, char **args,
					t_executer *ex);
void			reset_stdinout(t_executer *ex);
t_pipe			*init_pipes(int n_cmds);
int				init_redir(t_command *current);
t_executer		*init_executer(t_command *cmds);
int				count_commands(t_command *cmd);
int				handle_heredoc(t_shell *shell, t_redirection *red);
int				setup_input_redirections(t_command *cmd);
int				setup_output_redirections(t_command *cmd);
//builtins
int				echo_cmd(char **args);
int				env_cmd(t_shell *shell);
int				pwd_cmd(char **args);
int				exit_cmd(t_shell *shell, char **args, t_executer *ex);
int				cd_cmd(t_shell *shell);
int				export_cmd(t_shell *shell, char **args);
int				unset_cmd(t_shell *shell, char **args);

#endif
