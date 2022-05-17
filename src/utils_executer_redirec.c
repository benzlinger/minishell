#include "../include/minishell.h"

/**
 * 	@brief	checks if a redirec is a append redirec
 */
static bool	set_append(t_token_list *node)
{
	if (node->type != REDIREC)
		return (false);
	if (node->token[0] == '>' && node->token[1] == '>')
		return (true);
	else
		return (false);
}

/**
 * 	@brief	handles redirec and heredoc depending on the types
 */
static void	handle_types(t_token_list *head)
{
	t_token_list	*current;
	bool			append;

	append = false;
	current = head;
	while (current != NULL)
	{
		if (current->type == RIN)
			redirec_input(current);
		else if (current->type == HIN)
			redirec_heredoc_input(current);
		else if (current->type == ROUT)
			redirec_output(current, append);
		else if (current->type == TRUNC)
			truncate_file(current);
		else if (current->type == CREAT)
			create_file(current);
		append = set_append(current);
		current = current->next;
	}
}

/**
 * 	@brief	norm function
 */
static void	increment_until_next_comma(char *cmd, int *i)
{
	int	j;

	j = *i;
	cmd[j + 1] = ' ';
	cmd[j + 2] = ' ';
	while (cmd[j] && cmd[j] != ',')
		j++;
	*i = j;
}

/**
 * 	@brief	removes redirections and heredocs and the filename after them
 */
static char	*remove_redirec(char **command)
{
	char	*new_cmd;
	int		i;
	int		j;

	new_cmd = ft_calloc(ft_strlen(*command) + 1, sizeof(char));
	if (new_cmd == NULL)
		ft_error(strerror(errno));
	i = 0;
	j = 0;
	while (command[0][i])
	{
		while ((command[0][i] == '<' || command[0][i] == '>') && command[0][i])
			increment_until_next_comma(*command, &i);
		if (command[0][i])
		{
			new_cmd[j] = command[0][i];
			i++;
			j++;
		}
	}
	free(*command);
	return (new_cmd);
}

/**
 * 	@brief	handles redirections and heredocs
 * 	@param	cmd_line: the old 2d command line
 * 	@param	data: data struct
 * 	@return	a new 2d command line with removed redirections and tailored to the
 * 			commands
 */
char	**ft_redirec(char **cmd_line, t_data *data)
{
	char	**new_cmd_line;

	print_2d_array(cmd_line);
	handle_types(data->tokens);
	
	// FIXME
	// bc data->command is used here, the whole cmd_line
	// is used, what it shouldn't
	// also
	// redirections do not work at all in combination with pipes
	// at least after the first pipe
	
	data->command = remove_redirec(&data->command);
	data->command = remove_pipes(&data->command);
	new_cmd_line = ft_split(data->command, ',');
	free_2d_array(cmd_line);
	return (new_cmd_line);
}
