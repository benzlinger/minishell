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

//NORM ERROR
# define PRINT_HERE(){printf("In File: %s In Line: %d\n", __FILE__, __LINE__);}

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
	RIN,
	ROUT,
	TRUNC,
	CREAT,
	HIN,
	UNKNOWN
}		t_type;

/**
 *  pipe_index:	indexing token between pipes in command prompt, starting with 0
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
	int					fd;
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
	int				current_pipe;
	int				err_color;
	bool			redirec_exists;
	bool			heredoc_exists;
	bool			pipe_exists;
	int				builtin_fd;
}		t_data;

/* main functions */
t_token_list	*msh_lexer(char *line);
char			*msh_parser(t_data *data);
int				msh_executer(t_data *data, char **command);
t_vars			*init_vars(char **env_list);
void			init_signal_handling(int exit);

/* compatibility */
bool			redirection_found(t_token_list *head);
bool			heredoc_found(t_token_list *head);
bool			redirec_in(char **cmd_line);
char			*remove_pipes(char **old_cmd);

/* pipe functions */
int				pipe_exec(t_data *data); //test
char			**export_cmd(char *cmd);
int				exec_nopipe(t_data *data);
int				ft_wait(int pid);
char			*my_strjoin(char const *s1, char const *s2);

/* utils executer */
char			**ft_redirec(char **cmd_line, t_data *data);
void			redirec_input(t_token_list *node);
void			redirec_heredoc_input(t_token_list *node);
char			*remove_redirec(char **cmd_line);
void			redirec_output(t_token_list *node, bool append);
void			truncate_file(t_token_list *node);
void			create_file(t_token_list *node);
int				get_builtin_fd(t_data *data);
bool			set_append(t_token_list *node);
t_token_list	*iterate_to_current_pipe(t_data *data);
int				countyy(char **cmd_line);

/* utils parser */
char			*ft_list_to_str(t_token_list *tokens, char c);
char			*type_command(char **s, t_data *data);
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
int				check_redirections(t_token_list *head);
char			*find_env_var_value(t_data *data, char *name);

/* utils lexer */
void			remove_token_node(t_token_list *head, t_token_list **node);
int				ft_get_type(char *literal);
bool			ft_check_eof(char *s);
int				ft_get_pipe_index(char **prompt, int pos);
bool			ft_check_quote(char c, char *q);
char			*ft_delimit_line(char *pline, int i, int j);
bool			check_builtins(char *s);

/* utils error */
void			ft_error(char *err_msg);
void			ft_exit(int err_code);
void			ft_exit_eof(int err_code);
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
int				show_vars(t_vars *head, int fd);
t_vars			*new_var(char *name, char *value);

/* debug functions */
void			ft_print_list(t_token_list *head);
void			print_vars(t_vars *head);
void			ft_leaks(void);
char			*ft_color_format_str(char *s, char *pre, char **tofree);
void			print_2d_array(char **array);
int				get_size_2d(char **arr);
char			*get_type(int type);

/* builtin functions */
int				ft_echo(char **cmd_line, int fd);
int				ft_pwd(char **cmd_line, int fd);
int				ft_cd(char **cmd_line);
int				ft_env(t_data *data, char **cmd_line, int fd);
int				ft_export(t_data *data, char **cmd_line, int fd);
t_vars			*ft_unset(char **cmd_line, t_data *data);

#endif
