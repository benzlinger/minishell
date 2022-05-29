#include "../include/minishell.h"

int	get_last_redirec(t_token_list *head)
{
	t_token_list	*current;
	int				i;

	i = 0;
	current = head;
	while (current != NULL && current->type != PIPE)
	{
		if (current->type == REDIREC)
			i++;
		current = current->next;
	}
	current = head;
	while (current != NULL && i > 0)
	{
		if (current->type == REDIREC)
			i--;
		current = current->next;
	}
	i = current->index - 1;
	return (i);
}

void	set_rout(t_token_list *head, int i)
{
	t_token_list	*current;

	current = head;
	while (current != NULL && current->index != i)
		current = current->next;
	if (current != NULL && current->next != NULL)
		current->next->type = ROUT;
}

bool	rout_exists(t_token_list *head)
{
	t_token_list	*current;

	current = head;
	while (current != NULL)
	{
		if (current->type == REDIREC)
			if (current->token[0] == '>')
				return (true);
		current = current->next;
	}
	return (false);
}

void	set_rin_rout(t_token_list *head)
{
	t_token_list	*current;
	int				i;
	bool			newpipe;

	newpipe = true;
	current = head;
	while (current != NULL)
	{
		if (current->next != NULL && current->type == COMMAND)
			if (current->next->next != NULL && current->next->token[0] == '<')
				if (current->next->next->type != HIN)
					current->next->next->type = RIN;
		if (newpipe && rout_exists(head))
		{
			i = get_last_redirec(current);
			set_rout(current, i);
			newpipe = false;
		}
		if (current->type == PIPE)
			newpipe = true;
		current = current->next;
	}
}
