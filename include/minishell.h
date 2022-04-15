#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h> // printf, readline
# include <readline/readline.h> // readline
# include <readline/history.h> // readline
# include <unistd.h> // write, access
# include <stdlib.h> // malloc, free, exit
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
	PIPE
}		t_type;

/* 	pipe_index:	indexing token between pipes in command prompt, starting with 0
 * 	token:		literal string of token
 * 	type:		enumurated token type for identification
 * 	next:		pointer to next token. If it's the last token, next == NULL
 */
typedef struct s_token_list
{
	int			pipe_index;
	char			*token;
	t_type			type;
	struct s_token_list	*next;
}		t_token_list;

typedef struct s_vars
{
	struct s_vars		*next;
	char			*name;
	char			*value;
}		t_vars;

t_token_list	*msh_lexer(char *line);
void		init_signal_handling(void);

/* utils */
int		ft_get_pipe_index(char **prompt, int pos);
void		ft_error(char *err_msg);
void		ft_exit(int err_code);
void		ft_free_tokens(t_token_list **tokens);
bool		ft_check_EOF(char *s);
char		*ft_delimit_line(char *pline, int i, int j);
char		*msh_parser(t_token_list *tokens);
char		*ft_parse_error(char *err_msg1, char *err_msg2);
int		msh_executer(char *command);
int		ft_get_type(char *literal);
char		*ft_list_to_str(t_token_list *tokens, char c);

/* debug functions */
void		ft_print_list(t_token_list *head);

/* builtin functions */
int			ft_echo(char **cmd_line);
int			ft_pwd(void);
int			ft_cd(char *cmd_line);

#endif
