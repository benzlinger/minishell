#include "../include/minishell.h"

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
			g_exitstatus = 258;
			return (EXIT_FAILURE);
		}
		if (current->token[0] == '<' && current->type != HEREDOC)
		{
			if (access(current->next->token, F_OK) != 0)
			{
				current = current->next;
				ft_parse_error(current->token, ": No such file or directory");
				g_exitstatus = 1;
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

static int	check_redir_syntax(t_token_list *head)
{
	t_token_list	*tmp;

	tmp = head;
	// ft_print_list(tmp);
	while (tmp)
	{
		if (tmp->type == REDIREC)
		{
			if (!tmp->next || tmp->next->type == REDIREC
				|| tmp->next->type == PIPE || tmp->next->type == FLAG)
			{
				ft_parse_error("Invalid redirection syntax near: ", tmp->token);
				g_exitstatus = 258;
				return (EXIT_FAILURE);
			}
		}
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

int	check_redirections(t_token_list *head)
{
	if (!redirection_found(head) && !heredoc_found(head))
		return (EXIT_SUCCESS);
	if (check_left_redirec(head) != 0)
		return (EXIT_FAILURE);
	if (check_redir_syntax(head))
		return (EXIT_FAILURE);
	set_hin(head);
	set_rin_rout(head);
	set_flag_types(head);
	return (EXIT_SUCCESS);
}
