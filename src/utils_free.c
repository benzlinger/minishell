#include "../include/minishell.h"

/**
 * 	@brief	frees the token linked list
 * 	@param	pointer to the linked list headpointer
 */
void	ft_free_tokens(t_token_list **tokens)
{
	while (tokens[0] != NULL)
	{
		if (tokens[0]->type != ENVAR && tokens[0]->type != ENVARU)
			free(tokens[0]->token);
		free(*tokens);
		*tokens = tokens[0]->next;
	}
}

/*	@brief	free the whole list of env variables
 *	@params	head of env variable list
 *	@return	if node is found: node, else NULL
 */
void	free_vars(t_vars *head)
{
	t_vars	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head);
		head = tmp;
	}
}
