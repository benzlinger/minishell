#include "../include/minishell.h"

static int	check_tokens_via_type(t_token_list *head)
{
	t_token_list	*current;

	current = head;
	while (current != NULL)
	{
//		if (current->type == COMMAND)
//			current->token = ft_type_command(current);
		/*
		else if (current->type == ENVAR)
			current->token = ft_type_envar(current);
		else if (current->type == DQUOTE)
			current->token = ft_type_dquote(current);
		else if (current->type == SQUOTE)
			current->token = ft_type_squote(current);
		else if (current->type == REDIREC)
			current->token = ft_type_redirec(current);
		else if (curren->type == PIPE)
			current->token = ft_type_pipe(current);
		*/
		if (current->token == NULL)
			return (EXIT_FAILURE);
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
