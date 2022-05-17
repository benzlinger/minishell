#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h> // printf, readline
# include <readline/readline.h> // readline
# include <readline/history.h> // readline
# include <unistd.h> // write, access
# include <stdlib.h> // malloc, free, exit, getenv
# include <stdbool.h> // bool type, EXIT_SUCC/FAIL
# include <errno.h> // errno macro
# include <string.h> // strerror
# include <signal.h> // sigaction
# include <fcntl.h> // system(leaks)
# include "libft.h"

# define ERROR "\e[1;31mError: \e[0m"

typedef enum e_type
{
	COMMAND,
	BUILTIN,
	ENVAR,
	FLAG,
	DQUOTE,
	SQUOTE,
	REDIREC,
	HEREDOC,
	PIPE,
	UNKNOWN,
}		t_type;

/* 	pipe_index:	indexing token between pipes in command prompt, starting with 0
 * 	token:		literal string of token
 * 	type:		enumurated token type for identification
 * 	next:		pointer to next token. If it's the last token, next == NULL
 */
typedef struct s_token_list
{
	int					pipe_index;
	int					index;
	char				*token;
	t_type				type;
	struct s_token_list	*next;
}		t_token_list;

typedef struct s_vars
{
	struct s_vars	*next;
	char			*name;
	char			*value;
}		t_vars;

typedef struct s_data
{
	char			**env_list;
	t_token_list	*tokens;
	t_vars			*vars;
	char			*line;
	char			*command;
	char			**varray;
	int				exitstatus;
	pid_t			pid;
	int				status;
	int				fd[2];
}		t_data;

/* main functions */
t_token_list	*msh_lexer(char *line);
char			*msh_parser(t_data *data);
int				msh_executer(t_data *data, char **command);
t_vars			*init_vars(char **env_list);
void			init_signal_handling(int exit);

/* pipe functions */
int				pipe_exec(t_data *data); //test
char			**export_cmd(char *cmd);
int				exec_nopipe(t_data *data);
int				ft_wait(int pid);

/* utils parser */
char			*ft_list_to_str(t_token_list *tokens, char c);
char			*type_command(char **s);
char			*type_dquote(char **s, t_data *data);
char			*insert_envar(char **s, t_data *data);
bool			envar_exists(char *s);
int				type_pipe(char *s);
int				type_redirec(char *s);
char			*type_squote(char **s);
char			*type_envar(char **s);
char			*type_heredoc(char **s, char *token);
int				has_exitstatus(char *s);
char			*replace_exitstatus(char *s, t_data *data);

/* utils lexer */
int				ft_get_type(char *literal);
bool			ft_check_eof(char *s);
int				ft_get_pipe_index(char **prompt, int pos);
bool			ft_check_quote(char c, char *q);
char			*ft_delimit_line(char *pline, int i, int j);

/* utils error */
void			ft_error(char *err_msg);
void			ft_exit(int err_code);
char			*ft_parse_error(char *err_msg1, char *err_msg2);
void			ft_exec_error(char *err_msg1, t_data *data);

/* utils free */
void			free_2d_array(char **arr);
void			free_vars(t_vars *head);
void			ft_free_tokens(t_token_list **tokens);
void			free_3d_array(char ***arr);

/* utils export */
int				name_len(char *s);
char			*get_name(char *s);
char			*get_value(char *s);
int				show_vars(t_vars *head);
t_vars			*new_var(char *name, char *value);

/* debug functions */
void			ft_print_list(t_token_list *head);
void			print_vars(t_vars *head);
void			ft_leaks(void);
char			*ft_color_format_str(char *s, char *pre, char **tofree);
void			print_2d_array(char **array);
int				get_size_2d(char **arr);

/* builtin functions */
int				ft_echo(char **cmd_line);
int				ft_pwd(char **cmd_line);
int				ft_cd(char **cmd_line);
int				ft_env(t_data *data, char **cmd_line);
int				ft_export(t_data *data, char **cmd_line);
t_vars			*ft_unset(char **cmd_line, t_data *data);

#endif
