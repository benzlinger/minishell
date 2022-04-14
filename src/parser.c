#include "../include/minishell.h"

/**
 * 	@brief	gets size for allocating command string
 * 	@param	tokens: linked list from lexer
 * 	@return size for command string to be allocated with
 */
static int	get_command_size(t_token_list *tokens)
{
	t_token_list	*current;
	int		listlen;
	int		charlen;

	current = tokens;
	listlen = 0;
	charlen = 0;
	while (current != NULL)
	{
		charlen += ft_strlen(current->token);
		listlen++;
		current = current->next;
	}
	return (listlen + charlen);
}

/**	
 * 	@brief	norm function; also setting the delimiter for command string
 * 	@param	command: pointer to command string
 * 	@param	i: pointer to index
 * 	@param	c: the delimiter to set (standard is space ' ')
 */
static void	add_delimiter(char **command, int *i, char c)
{
	command[0][*i] = c;
	*i += 1;
}

/**
 * 	@brief	turns the token list into a single string with a set delimiter
 * 	@param	tokens: linked list from lexer
 * 	@param	c: the delimiter to set (standard is space ' ')
 * 	@return	command string
 */
static char	*ft_list_to_str(t_token_list *tokens, char c)
{
	t_token_list	*current;
	char		*command;
	int		size;
	int		i;
	int		j;

	size = get_command_size(tokens);
	command = ft_calloc(size + 1, sizeof(char));
	if (command == NULL)
		ft_error(strerror(errno));
	current = tokens;
	i = 0;
	while (current != NULL)
	{
		j = 0;
		while (current->token[j])
		{
			command[i] = current->token[j];
			i++;
			j++;
		}
		add_delimiter(&command, &i, c);
		current = current->next;
	}
	return (command);
}

/**
 * 	@brief	checks input for errors and returns a rdy-to-run command string
 * 	@param	tokens: linked list from lexer
 * 	@return	ready-to-run command string
 */
char	*msh_parser(t_token_list *tokens)
{
	char	*command;

	/*
	if (check_commands(tokens) != 0)
		return (NULL);
	if (check_quotes(tokens) != 0)
		return (NULL);
	*/
	command = ft_list_to_str(tokens, ' ');
	return(command);
}
