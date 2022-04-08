#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h> // readline
# include <readline/history.h> // readline
# include <stdio.h> // printf, readline
# include <stdlib.h>
# include <stdbool.h> // bool type, EXIT_SUCC/FAIL
# include "libft.h"

# define ERROR "\e[1;31mError: \e[0m"

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

t_token_list	msh_lexer(char *line);

#endif
