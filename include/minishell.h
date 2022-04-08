#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h> // printf, readline
# include <readline/readline.h> // readline
# include <readline/history.h> // readline
# include <unistd.h> // write
# include <stdlib.h> // malloc, free
# include <stdbool.h> // bool type, EXIT_SUCC/FAIL
# include "libft.h"

# define ERROR "\e[1;31mError: \e[0m"

typedef enum e_rror
{
	ALLOC
}		t_rror;

/*	random types from wikipedia for testing
 *	idk what exact types we'll need later
 */
typedef enum e_type
{
	IDENTIFIER,
	KEYWORD,
	SEPERATOR,
	OPERATOR,
	LITERAL,
	COMMENT
}		t_type;

/* 	pipe_index:	indexing token between pipes in command prompt, starting with 0
 * 	token:		literal string of token
 * 	type:		enumurated token type for identification
 * 	next:		pointer to next token. If it's the last token, next == NULL
 */
typedef struct s_token_list{
	int			pipe_index;
	char			*token;
	t_type			type;
	struct s_token_list	*next;
}		t_token_list;

t_token_list	*msh_lexer(char *line);

/* utils */
int		ft_get_pipe_index(char **prompt, int pos);
int		ft_error(int status);

/* debug functions */
void		ft_print_list(t_token_list *head);

#endif
