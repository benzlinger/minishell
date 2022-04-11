#include "../include/minishell.h"

/*	@brief	initializes the token linked list
 *	@param	literal: the first token of the command prompt
 *	@return	linked list head pointer
 */
static t_token_list	*init_token_list(char *literal)
{
	t_token_list	*head;

	head = ft_calloc(1, sizeof(t_token_list));
	if (head == NULL)
		ft_error(strerror(errno));
	head->token = ft_strdup(literal);
	// head->type function 
	head->pipe_index = 0;
	head->next = NULL;
	return (head);
}

/*	@brief	function to add token nodes to the linked list
 *	@param	literal: complete command prompt
 *	@param	head: first tokennode of linked list
 *	@param	i: position in literal
 */
static void	add_token_node(char **literal, t_token_list *head, int i)
{
	t_token_list	*node;
	t_token_list	*current;

	node = ft_calloc(1, sizeof(t_token_list));
	if (node == NULL)
		ft_error(strerror(errno));
	current = head;
	while (current->next != NULL)
		current = current->next;
	current->next = node;
	node->token = ft_strdup(literal[i]);
	node->pipe_index = ft_get_pipe_index(literal, i);
	// node->type function 
	node->next = NULL;
}

/*	@brief	split command line into tokens
 *	@params	command line
 *	@return	pointer to head of token list
 *	FIXME what if tokens[0] == NULL?
 */
t_token_list	*msh_lexer(char *line)
{
	t_token_list	*head;
	char		**tokens;
	int		count;

	tokens = ft_split(line, ' ');
	head = init_token_list(tokens[0]);
	count = 1;
	while (tokens[count])
	{
		add_token_node(tokens, head, count);
		count++;
	}
	while (count >= 0)
	{
		free(tokens[count]);
		count--;
	}
	free(tokens);
	return (head);
}
