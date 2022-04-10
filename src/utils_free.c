#include "../include/minishell.h"

void	ft_free_tokens(t_token_list **tokens)
{
	while (tokens[0] != NULL)
	{
		free(*tokens);
		*tokens = tokens[0]->next;
	}
}
