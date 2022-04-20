#include "../include/minishell.h"

/**
 * 	@brief	runs function depending on tokentype
 * 		and makes them fit for the executer
 * 	@param	head: token list
 * 	@return	1: if an parse error occures
 * 		0: if successful
 */
static int	check_tokens_via_type(t_token_list *head)
{
	t_token_list	*current;

	current = head;
	while (current != NULL)
	{
		if (current->type == COMMAND)
			current->token = type_command(&current->token);
		else if (current->type == ENVAR || current->type == ENVARU)
			current->token = type_envar(&current->token);
		else if (current->type == DQUOTE)
			current->token = type_dquote(&current->token);
		else if (current->type == SQUOTE)
			current->token = type_squote(&current->token);
		else if (current->type == REDIREC)
			if (type_redirec(current->token) != 0)
				return (EXIT_FAILURE);
		/*
		else if (curren->type == PIPE)
			current->token = type_pipe(current);
		*/
		if (current->token == NULL)
			return (EXIT_FAILURE);
		current = current->next;
	}
	return (EXIT_SUCCESS);
}

static int	ft_ft(t_token_list *a)
{
	int	b;
	int	c;

	b = COMMAND;
	c = BUILTIN;
	if (a->type != ENVARU)
		return (b);
	if (a->next != NULL)
		return (b);
	printf("%s... you're turning into a penguin. Stop it.\n", a->token);
	return (c);
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
	if (ft_ft(tokens) != 0)
		return (NULL);
	/*
	if (check_commands(tokens) != 0)
		return (NULL);
	if (check_quotes(tokens) != 0)
		return (NULL);
	*/
	// return (ft_parse_error(tokens->token, ": command not found"));

	command = ft_list_to_str(tokens, ',');
	return(command);
}
