#include "../include/minishell.h"

/**
 * 	@brief	checks if a redirec is a append redirec
 */
bool	set_append(t_token_list *node)
{
	if (node->type != REDIREC)
		return (false);
	if (node->token[0] == '>' && node->token[1] == '>')
		return (true);
	else
		return (false);
}

t_token_list	*iterate_to_current_pipe(t_data *data)
{
	t_token_list	*current;

	current = data->tokens;
	while (current != NULL && current->pipe_index <= data->current_pipe)
		current = current->next;
	// FIXME last pipe wont work
	if (current == NULL)
		return (data->tokens);
	return (current);
}
/**
 * 	@brief	handles redirec and heredoc depending on the types
 */
static void	handle_types(t_data *data)
{
	t_token_list	*current;
	bool			append;

	append = false;
	current = iterate_to_current_pipe(data);
	while (current != NULL && current->type != PIPE)
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

static int	twod_elems(char **cmd_line)
{
	int	i;

	i = 0;
	while (cmd_line[i])
		i++;
	return (i * 4);
}

int	countyy(char **cmd_line)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (cmd_line[i] != NULL)
	{
		while (cmd_line[i][j] != '\0')
		{
			count++;
			j++;
		}
		j = 0;
		i++;
	}
	return (count);
}

// FIXME
// somethings going wrong with grep and awk after a pipe
char	*remove_redirec(char **cmd_line)
{
	char	*cmd;
	int		i;
	int		j;
	int		k;

	cmd = ft_calloc(countyy(cmd_line), sizeof(char));
	if (cmd == NULL)
		ft_error(strerror(errno));
	i = 0;
	j = 0;
	while (cmd_line[i])
	{
		k = 0;
		while (cmd_line[i] && (cmd_line[i][k] == '<' || cmd_line[i][k] == '>'))
			i += 2;
		if (!cmd_line[i])
			break ;
		while (cmd_line[i][k])
		{
			cmd[j] = cmd_line[i][k];
			j++;
			k++;
		}
		cmd[j] = ',';
		j++;
		i++;
	}
	while (cmd[j])
	{
		cmd[j] = '\0';
		j++;
	}
	return (cmd);
}

void	remove_tmp(t_data *data)
{
	char	**cmd_line;
	int		pid;

	if (access(".tmp.txt", F_OK) == 0)
	{
		cmd_line = malloc(sizeof(char *) * 3);
		cmd_line[0] = "/bin/rm";
		cmd_line[1] = ".tmp.txt";
		cmd_line[2] = NULL;
		pid = fork();
		if (pid == -1)
			ft_error(strerror(errno));
		else if (pid == 0)
			execve(cmd_line[0], cmd_line, data->env_list);
		else
		{
			wait(NULL);
			free(cmd_line);
		}
	}
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
	char	*cmd;

	handle_types(data);
	cmd = remove_redirec(cmd_line);
	new_cmd_line = ft_split(cmd, ',');
	free(cmd);
	remove_tmp(data);
	return (new_cmd_line);
}
