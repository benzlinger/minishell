#include "../include/minishell.h"

int	check_redirections(t_token_list *head)
{
	if (check_left_redirec(head) != 0)
		return (EXIT_FAILURE);
	if (
}
