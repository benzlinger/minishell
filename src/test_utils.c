#include "../include/minishell.h"

bool	redirection_found(t_token_list *head)
{
	t_token_list	*current;

	current = head;
	while (current != NULL)
	{
		if (current->type == REDIREC)
			return (true);
		current = current->next;
	}
	return (false);
}

void	ft_redirect(char **cmd_line, t_data *data)
{
	printf("ft_redirect in test_utils.c\n");
}
