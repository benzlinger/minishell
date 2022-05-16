#include "../include/minishell.h"

static void	redirec_input(t_token_list *node)
{
	node->fd = open(node->token, O_RDONLY);
	if (node->fd == -1)
		ft_error(strerror(errno));
	if (dup2(node->fd, STDIN_FILENO) == -1)
		ft_error(strerror(errno));
	if (close(node->fd) == -1)
		ft_error(strerror(errno));
}

static bool	set_append(t_token_list *node)
{
	if (node->type != REDIREC)
		return (false);
	if (node->token[0] == '>' && node->token[1] == '>')
		return (true);
	else
		return (false);
}

static void	handle_types(t_token_list *head)
{
	t_token_list	*current;
	bool			append;

	current = head;
	while (current != NULL)
	{
		// FIXME move append to ROUT func
		append = set_append(current);
		if (current->type == RIN)
			redirec_input(current);
		/*
		else if (current->type == HIN)
			redirec_heredoc_input(current);
		else if (current->type == ROUT)
			redirec_output(current, append);
		else if (current->type == TRUNC)
			truncate_file(current);
		else if (current->type == CREAT)
			create_file(current);
		*/
		current = current->next;
	}
}

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
		{
			i++;
		}
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

char	**ft_redirec(char **cmd_line, t_data *data)
{
	char	**new_cmd_line;

	handle_types(data->tokens);
	data->command = remove_redirec(&data->command);
	new_cmd_line = ft_split(data->command, ',');
	free_2d_array(cmd_line);
	return (new_cmd_line);
}
