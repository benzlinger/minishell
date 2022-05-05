#include "../include/minishell.h"

static int	check_tokens_via_type2(t_token_list *cur)
{
	if (cur->type == HEREDOC)
	{
		cur->token[1] = '\0';
		cur->next->token = type_heredoc(&cur->next->token, cur->next->token);
	}
	if (cur->type == REDIREC)
		if (type_redirec(cur->token) != 0)
			return (EXIT_FAILURE);
	if (cur->type == PIPE)
		if (type_pipe(cur->token) != 0)
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
 * 	@brief	runs function depending on tokentype
 * 			and makes them fit for the executer
 * 	@param	head: token list
 * 	@return	1: if an parse error occures
 * 			0: if successful
 */
static int	check_tokens_via_type(t_token_list *head)
{
	t_token_list	*current;

	current = head;
	while (current != NULL)
	{
		if (current->type == ENVAR)
			current->token = insert_envar(&current->token);
		else if (current->type == DQUOTE)
			current->token = type_dquote(&current->token);
		else if (current->type == SQUOTE)
			current->token = type_squote(&current->token);
		if (check_tokens_via_type2(current) != 0)
			return (EXIT_FAILURE);
		if (current->token == NULL)
			return (EXIT_FAILURE);
		current = current->next;
	}
	return (EXIT_SUCCESS);
}

/**
 * 	@brief	the very first token and every token after a pipe gets
 * 			converted to COMMAND unless it's a BUILTIN
 * 	@param	head: head of token list
 * 	@return Success or failure
 */
static int	get_command_types(t_token_list *head)
{
	t_token_list	*current;

	current = head;
	if (current->type != BUILTIN)
	{
		current->type = COMMAND;
		current->token = type_command(&current->token);
		if (current->token == NULL)
			return (EXIT_FAILURE);
	}
	while (current != NULL)
	{
		if (current->type == PIPE)
		{
			if (current->next == NULL)
				return ((int)ft_parse_error("invalid pipe syntax", NULL) + 1);
			current->next->type = COMMAND;
			current->next->token = type_command(&current->next->token);
			if (current->token == NULL)
				return (EXIT_FAILURE);
		}
		current = current->next;
	}
	return (EXIT_SUCCESS);
}

/**
 * 	@brief	checks input for errors and returns a rdy-to-run command string
 * 	@param	tokens: linked list from lexer
 * 	@return	ready-to-run command string
 */
char	*msh_parser(t_token_list *tokens)
{
	char	*command;

	if (check_tokens_via_type(tokens) != 0)
		return (NULL);
	if (get_command_types(tokens) != 0)
		return (NULL);
	command = ft_list_to_str(tokens, ',');
	return (command);
}
