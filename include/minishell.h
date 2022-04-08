#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h> // readline
# include <readline/history.h> // readline
# include <stdio.h> // printf, readline
# include <stdlib.h>
# include <stdbool.h> // bool type, EXIT_SUCC/FAIL
# include "libft.h"

# define ERROR "\e[1;31mError: \e[0m"

int		lexer(char *line);

#endif
