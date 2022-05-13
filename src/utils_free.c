#include "../include/minishell.h"

/**
 * 	@brief	frees the token linked list
 * 	@param	pointer to the linked list headpointer
 */
void	ft_free_tokens(t_token_list **tokens)
{
	while (tokens[0] != NULL)
	{
		//if (tokens[0]->type != ENVAR && tokens[0]->type != ENVARU)
		//	free(tokens[0]->token);
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
		if (head->name)
			free(head->name);
		if (head->value)
			free(head->value);
		free(head);
		head = tmp;
	}
}

/*	@brief	free 2 dimensional array and its contents
 *	@params	array to free
 */
void	free_2d_array(char **arr)
{
	int	i;

	if (arr)
	{
		i = 0;
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
		free(arr);
	}
}

void	free_3d_array(char ***arr)
{
	int	i;

	if (arr)
	{
		i = 0;
		while (arr[i])
		{
			free_2d_array(arr[i]);
			i++;
		}
		free(arr);
	}
}
