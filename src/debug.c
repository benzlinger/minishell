/* CAUTION
 * This file exists only for debugging purposes
 * and should be removed by the projects completion
 */

#include "../include/minishell.h"

void	ft_print_list(t_token_list *head)
{
	t_token_list	*current;

	current = head;
	while (current != NULL)
	{
		printf("pipe_index:\t%i\n", current->pipe_index);
		printf("token:\t\t%s\n", current->token);
		printf("type:\t\t%i\n", current->type);
		printf("next:\t\t%p\n", current->next);
		printf("\n");
		current = current->next;
	}
}
