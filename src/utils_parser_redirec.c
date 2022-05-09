#include "../include/minishell.h"

/**
 * 	FIXME
 * 	if a file with type ROUT does not exist theres a problem
 * 	this file can't be ROUT and CREAT at the same time.
 *
 * 	Also the types are sometimes off, might be related to the issue above
 * 	but that is not necessarily the case.
 */

static int	get_last_redirec(t_token_list *head)
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
	return (i);
}

static void	set_rout(t_token_list *head, int i)
{
	t_token_list	*current;

	current = head;
	while (current->index != i && current != NULL)
		current = current->next;
	current->type = ROUT;
}

static void	set_rin_rout(t_token_list *head)
{
	t_token_list	*current;
	int				i;
	bool			newpipe;

	newpipe = true;
	current = head;
	while (current != NULL)
	{
		if (current->type == COMMAND && current->next != NULL)
			if (current->next->token[0] == '<' && current->next->next != NULL)
				current->next->next->type = RIN;
		if (newpipe)
		{
			i = get_last_redirec(current);
			set_rout(head, i);
			newpipe = false;
		}
		if (current->type == PIPE)
			newpipe = true;
		current = current->next;
	}
}

static void	set_flag_types(t_token_list *head)
{
	t_token_list	*current;

	current = head;
	while (current->next != NULL)
	{
		if (current->type == REDIREC)
		{
			if (current->next->type != RIN && current->next->type != ROUT)
			{
				if (access(current->next->token, F_OK) != 0)
					current->next->type = CREAT;
				else
					current->next->type = TRUNC;
			}
		}
		current = current->next;
	}
}

static int	check_left_redirec(t_token_list *head)
{
	t_token_list	*current;

	current = head;
	while (current->next != NULL)
	{
		if (current->type != COMMAND && current->next->token[0] == '<')
		{
			ft_parse_error("Invalid redirection syntax near: ", current->token);
			return (EXIT_FAILURE);
		}
		if (current->token[0] == '<')
		{
			if (access(current->next->token, F_OK) != 0)
			{
				current = current->next;
				ft_parse_error(current->token, ": No such file or directory");
				return (EXIT_FAILURE);
			}
		}
		current = current->next;
	}
	return (EXIT_SUCCESS);
}

int	check_redirections(t_token_list *head)
{
	if (redirection_found(head) == false)
		return (EXIT_SUCCESS);
	if (check_left_redirec(head) != 0)
		return (EXIT_FAILURE);
	set_rin_rout(head);
	set_flag_types(head);
	ft_print_list(head);
	return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
