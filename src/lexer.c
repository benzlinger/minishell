#include "../include/minishell.h"

static t_token_list	init_token_list(char *literal)
{
	t_token_list	*head;

	head = ft_calloc(1, sizeof(t_token_list));
	if (head == NULL)
		ft_error(ALLOC);
	// FIXME free head.token
	head->token = ft_strdup(literal);
	// head.type && head.pipe_index functions
	head->next = NULL;
	return (head);
}

static void	add_token_node(char *literal, t_token_list *head)
{
	t_token_list	*node;
	t_token_list	*current;

	node = ft_calloc(1, sizeof(t_token_list));
	if (node == NULL)
		ft_error(ALLOC);
	current = head;
	while (current != NULL)
		current = current->next;
	current->next = node;
	// FIXME free node->token
	node->token = ft_strdup(literal);
	// node->token && node->pipe_index functions
	node->next = NULL;
}

/*	split command line
 *	into tokens
 *	@params	command line
 *	@return	1 on success
 *	FIXME what if tokens[0] == NULL?
 */
t_token_list	msh_lexer(char *line)
{
	t_token_list	*head;
	char		**tokens;
	int		count;

	tokens = ft_split(line, ' ');
	head = init_token_list(tokens[0]);
	count = 0;
	while (tokens[count])
	{
		add_token_node(tokens[count], head);
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
