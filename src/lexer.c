#include "../include/minishell.h"

/**
 * 	@brief	initializes the token linked list
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
	head->type = ft_get_type(head->token);
	head->pipe_index = 0;
	head->index = 0;
	head->next = NULL;
	return (head);
}

/**
 * 	@brief	function to add token nodes to the linked list
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
	node->type = ft_get_type(node->token);
	node->pipe_index = ft_get_pipe_index(literal, i);
	node->index = i;
	node->next = NULL;
}

/**
 * 	@brief	split command line into tokens
 *	@params	command line
 *	@return	pointer to head of token list
 */
t_token_list	*msh_lexer(char *promptline)
{
	t_token_list	*head;
	char			**literal;
	int				count;
	char			*delimited_line;

	delimited_line = ft_delimit_line(promptline, 0, 0);
	literal = ft_split(delimited_line, ',');
	head = init_token_list(literal[0]);
	count = 1;
	while (literal[count])
	{
		add_token_node(literal, head, count);
		count++;
	}
	while (count >= 0)
	{
		free(literal[count]);
		count--;
	}
	free(literal);
	free(delimited_line);
	return (head);
}
