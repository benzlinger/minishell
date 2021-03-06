/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btenzlin <btenzlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:22:40 by btenzlin          #+#    #+#             */
/*   Updated: 2022/06/02 10:42:16 by btenzlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

# define ERROR "\001\033[1;31mError:\002 \001\033[0m\002"
# define CYAN "\001\033[36m\002"
# define BCYAN "\001\033[1;36m\002"
# define YELLOW "\001\033[1;33m\002"
# define PURPLE "\001\033[1;95m\002"
# define RESET "\001\033[0m\002"

int	g_exitstatus;

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
	TOKEN,
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
void			init_signal_handling(void);
char			*msh_prompt(t_data *data);

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
void			check_for_substitute_char(char **cmd_array);

/* utils executer */
void			remove_tmp(t_data *data);
char			**ft_redirec(char **cmd_line, t_data *data);
void			redirec_input(t_token_list *node);
void			redirec_heredoc_input(t_token_list *node);
char			*remove_redirec(char **cmd_line, int i, int j);
void			redirec_output(t_token_list *node, bool append);
void			truncate_file(t_token_list *node);
void			create_file(t_token_list *node);
int				get_builtin_fd(t_data *data);
bool			set_append(t_token_list *node);
t_token_list	*iterate_to_current_pipe(t_data *data);
int				countyy(char **cmd_line);
void			init_child_handling(void);

/* utils parser */
int				get_last_redirec(t_token_list *head);
void			set_rout(t_token_list *head, int i);
bool			rout_exists(t_token_list *head);
void			set_rin_rout(t_token_list *head);
char			*ft_list_to_str(t_token_list *tokens, char c);
char			*type_command(char **s, t_data *data);
char			*type_dquote(char **s, t_data *data);
char			*insert_envar(char **s, t_data *data);
bool			envar_exists(char *s);
int				type_pipe(char *s);
int				type_redirec(char *s);
char			*type_squote(char **s);
char			*type_heredoc(char **s, char *token);
int				has_exitstatus(char *s);
char			*replace_exitstatus(char *s);
int				check_redirections(t_token_list *head);
char			*find_env_var_value(t_data *data, char *name);
int				quote_count(char *s, char c);
void			set_token_type(t_token_list *head);

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
int				ft_exec_error(char *err_msg1, t_data *data);

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
int				find_var(char *name, char *value, t_vars *head);
t_vars			*append_var(char *name, char *value, t_vars *head);
t_vars			*init_vars(char **env_list);

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
int				ft_cd(char **cmd_line, int ret, char *user);
int				ft_env(t_data *data, char **cmd_line, int fd);
int				ft_export(t_data *data, char **cmd_line, int fd, int is_exit);
t_vars			*ft_unset(char **cmd_line, t_data *data);
int				ft_exit_builtin(char **cmd_line);

#endif
