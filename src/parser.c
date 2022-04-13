#include "../include/minishell.h"

char	*msh_parser(t_token_list *tokens)
{
	return(ft_parse_error(tokens->token, ": command not found"));
}
