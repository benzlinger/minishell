#include "../include/minishell.h"

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

static void	set_rout(t_token_list *head, int i)
{
	t_token_list	*current;

	current = head;
	while (current != NULL && current->index != i)
		current = current->next;
	if (current->next != NULL)
		current->next->type = ROUT;
}

static bool	rout_exists(t_token_list *head)
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

static void	set_rin_rout(t_token_list *head)
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
			i = get_last_redirec(head);
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
		if (current->type != COMMAND && current->next->token[0] == '<'
				&& current->next->type != HEREDOC)
		{
			ft_parse_error("Invalid redirection syntax near: ", current->token);
			return (EXIT_FAILURE);
		}
		if (current->token[0] == '<' && current->type != HEREDOC)
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

static void	set_hin(t_token_list *head)
{
	t_token_list	*current;

	current = head;
	while (current != NULL && current->type != HEREDOC)
		current = current->next;
	if (current != NULL && current->next != NULL && current->type == HEREDOC)
		current->next->type = HIN;
}

int	check_redirections(t_token_list *head)
{
	if (!redirection_found(head) && !heredoc_found(head))
		return (EXIT_SUCCESS);
	if (check_left_redirec(head) != 0)
		return (EXIT_FAILURE);
	set_hin(head);
	set_rin_rout(head);
	set_flag_types(head);
	return (EXIT_SUCCESS);
}
