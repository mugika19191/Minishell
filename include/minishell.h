/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enetxeba <enetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:10:07 by enetxeba          #+#    #+#             */
/*   Updated: 2025/04/10 12:22:52 by enetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "../include/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/resource.h>
# include <sys/wait.h>
# include <unistd.h>

enum					e_error_type
{
	ERROR_MALLOC,
	ERROR_OPEN_FILE,
	ERROR_NULL_POINTER
};

enum					e_link_type
{
	TOKEN_PIPE,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_EOF,
	TOKEN_NONE
};

enum					e_redir_type
{
	REDIR_IN,
	REDIR_HEREDOC,
	REDIR_OUT,
	REDIR_OUT_APPEND,
	REDIR_NONE
};

typedef struct s_token
{
	char				**command;
	enum e_link_type	type;
	int					redir_type;
	char				*filename;
	struct s_token		*next;
}						t_token;

typedef struct t_pipes
{
	pid_t				pid;
	pid_t				pid_shell;
	int					pipe_fd[2];
	int					prev_pipe[2];
	int					status;
	struct rusage		usage;
	int					prog_flow;
	char				***env;
	int					saved_stdout;
	int					saved_stdin;
	int					error_flag;
	char				*flag_str;
	char				*promp;
}						t_pipe;

# ifndef G_ENV_POINTER_H
#  define G_ENV_POINTER_H

extern void	*g_env_pointer;

# endif

int						ft_strcmp(const char *s1, const char *s2);
int						ft_arraylen(char **str);
int						is_connector(char *str);
t_token					*tokenizer(char **str);
void					link_type(t_token *token, char **str, int *c);
t_token					*new_token(char **str, int *c);
t_token					*ms_lstlast(t_token *lst);
t_token					*ms_lstadd_back(t_token *lst, t_token *new);

int						exe_token(t_token *token, t_pipe *pipes);
void					redirecctions(t_token *token);
void					parent(t_token *token, int pipe_fd[], int prev_pipe[]);
int						piper(t_token *token, int pipe_fd[]);

int						is_in_out(char *str);
void					add_filename(t_token *token, char **str, int *c);
void					redir_out(t_token *token, t_pipe *conf);
char					*joinpath(t_token *token, t_pipe *conf);
void					redirec(t_token *token, t_pipe *conf);
void					heredoc(t_token *token, t_pipe *pipe_fd);
void					redir_in(t_token *token, t_pipe *conf);
void					init_pipes(t_pipe *fd_pipes, char ***env);
int						init_sigaction(struct sigaction *sig, t_pipe *pipe);
void					int_hadler(int sig, siginfo_t *info, void *context);
char					*find_var(char *var, char **env);
int						quote_check(char *str);
char					*get_next_dolar(const char *string, char *var);
char					**shell_split(char const *s, char c);
int						is_in_quotes(char const *str, int pos);
void					clean_token(t_token *token);
void					clean_command(char **str);
int						pt_lstsize(t_token *lst);
void					father(t_token *token, t_pipe *pipe_fd);
int						get_var_len(char *str);
char					*get_var(char *str, t_pipe *pipes);
char					*replace_var(char *str, t_pipe *pipes);
int						read_line(t_pipe *pipes);
char					*create_prompt(char *str, char **env);
char					*search_command(char *comand, t_pipe *conf);
void					redir_type(t_token *token, char **str, int *c);
void					exec_built_in(t_token *token, t_pipe *conf, int exit);
int						built_in(char *str);
void					pwd(t_pipe *conf);
void					env(t_token *token, t_pipe *conf);
void					echo(t_token *token, t_pipe *conf);
char					**export(t_pipe *pipes, char *str);
char					**unset(t_pipe *pipes, char *str);
int						cd(t_token *token, t_pipe *pipes);
void					ft_exit(t_pipe *conf);
int						is_valid_env_var(char *str);
int						env_len(char **env);
void					clean_quotes(t_token *token);
char					**edit_env(t_pipe *pipes, char *str);
char					*cd_change_directory(const char *target, char *old_pwd);
int						read_line(t_pipe *pipes);
void					read_line_body(char *promp, t_pipe *pipes, char *line);
void					heredoc(t_token *token, t_pipe *pipe_fd);
int						spaces(char *str);
int						set_flag(t_pipe *pipes, int error);
#endif
