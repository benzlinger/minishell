#include "../include/minishell.h"

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
