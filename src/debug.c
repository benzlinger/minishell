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
		printf("index:\t\t%i\n", current->index);
		printf("token:\t\t%s\n", current->token);
		printf("type:\t\t%i\n", current->type);
		printf("next:\t\t%p\n", current->next);
		printf("\n");
		current = current->next;
	}
}

void	print_vars(t_vars *head)
{
	t_vars	*tmp;

	tmp = head;
	if (!tmp)
		printf("Empty list.\n");
	while (tmp)
	{
		printf("%s", tmp->name);
		if (tmp->value)
			printf(" =%s", tmp->value);
		printf("\n");
		tmp = tmp->next;
	}
}

void	ft_leaks(void)
{
	system("leaks minishell");
}

void	print_2d_array(char **array)
{
	int	i;

	if (!array)
		printf("Array empty.\n");
	i = 0;
	while (array[i])
	{
		printf("%s ", array[i]);
		i++;
	}
	printf("\n");
}

/*	@brief	get size of 2d array
 *	@params	2d array
 *	@return	size of array
 */
int	get_size_2d(char **arr)
{
	int	i;

	if (!arr)
		return (0);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}
