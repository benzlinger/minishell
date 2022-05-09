/* CAUTION
 * This file exists only for debugging purposes
 * and should be removed by the projects completion
 */

#include "../include/minishell.h"

static char	*get_type(int type)
{
	switch(type)
	{
		case 0:		return ("COMMAND");	break;
		case 1: 	return ("BUILTIN");	break;
		case 2:		return ("ENVAR");	break;
		case 3:		return ("FLAG");	break;
		case 4:		return ("DQUOTE");	break;
		case 5:		return ("SQUOTE");	break;
		case 6:		return ("REDIREC");	break;
		case 7:		return ("HEREDOC");	break;
		case 8:		return ("PIPE");	break;
		case 9:		return ("RIN");		break;
		case 10:	return ("ROUT");	break;
		case 11:	return ("TRUNC");	break;
		case 12:	return ("CREAT");	break;
		default:	return ("UNKNOWN");	break;
	}
	return (NULL);
}

void	ft_print_list(t_token_list *head)
{
	t_token_list	*current;

	current = head;
	while (current != NULL)
	{
		printf("pipe_index:\t%i\n", current->pipe_index);
		printf("index:\t\t%i\n", current->index);
		printf("token:\t\t%s\n", current->token);
		printf("type:\t\t%s\n", get_type(current->type));
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
