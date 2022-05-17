#include "../include/minishell.h"

char	*remove_pipes(char **old_cmd)
{
	char	*new_cmd;
	int		i;

	new_cmd = ft_calloc(ft_strlen(*old_cmd) + 1, sizeof(char));
	if (new_cmd == NULL)
		ft_error(strerror(errno));
	i = 0;
	while (old_cmd[0][i])
	{
		if (old_cmd[0][i] == '|' && old_cmd[0][i - 1] == ','
				&& old_cmd[0][i + 1] == ',')
			new_cmd[i] = ',';
		else
			new_cmd[i] = old_cmd[0][i];
		i++;
	}
	free(*old_cmd);
	return (new_cmd);
}

bool	redirec_in(char **cmd_line)
{
	int	i;

	i = 0;
	while (cmd_line[i])
	{
		if (cmd_line[i][0] == '<' || cmd_line[i][0] == '>')
			return (true);
		i++;
	}
	return (false);
}

bool	heredoc_found(t_token_list *head)
{
	t_token_list	*current;

	current = head;
	while (current != NULL && current->type != PIPE)
	{
		if (current->type == HEREDOC)
			return (true);
		current = current->next;
	}
	return (false);
}

bool	redirection_found(t_token_list *head)
{
	t_token_list	*current;

	current = head;
	while (current != NULL && current->type != PIPE)
	{
		if (current->type == REDIREC)
			return (true);
		current = current->next;
	}
	return (false);
}
