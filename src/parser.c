#include "../include/minishell.h"

static char	*type_command(char **s)
{
	char	*tmp;
	char	*path;

	tmp = ft_strdup("/bin/");
	path = ft_strjoin(tmp, *s);
	free(tmp);
	if (access(path, F_OK) != 0)
		return (ft_parse_error(*s, ": command not found"));
	free(*s);
	return (path);
}

static int	check_tokens_via_type(t_token_list *head)
{
	t_token_list	*current;

	current = head;
	while (current != NULL)
	{
		if (current->type == COMMAND)
			current->token = type_command(&current->token);
		/*
		else if (current->type == ENVAR)
			current->token = type_envar(current);
		else if (current->type == DQUOTE)
			current->token = type_dquote(current);
		else if (current->type == SQUOTE)
			current->token = type_squote(current);
		else if (current->type == REDIREC)
			current->token = type_redirec(current);
		else if (curren->type == PIPE)
			current->token = type_pipe(current);
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
