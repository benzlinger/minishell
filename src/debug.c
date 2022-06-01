/* CAUTION
 * This file exists only for debugging purposes
 * and should be removed by the projects completion
 */

#include "../include/minishell.h"

char	*get_type(int type)
{
	switch(type)
	{
		case 0:		return ("\e[93mCOMMAND\e[0m");	break;
		case 1: 	return ("\e[93mBUILTIN\e[0m");	break;
		case 2:		return ("\e[93mENVAR\e[0m");	break;
		case 3:		return ("\e[93mFLAG\e[0m");		break;
		case 4:		return ("\e[93mDQUOTE\e[0m");	break;
		case 5:		return ("\e[93mSQUOTE\e[0m");	break;
		case 6:		return ("\e[93mREDIREC\e[0m");	break;
		case 7:		return ("\e[93mHEREDOC\e[0m");	break;
		case 8:		return ("\e[93mPIPE\e[0m");		break;
		case 9:		return ("\e[93mRIN\e[0m");		break;
		case 10:	return ("\e[93mROUT\e[0m");		break;
		case 11:	return ("\e[93mTRUNC\e[0m");	break;
		case 12:	return ("\e[93mCREAT\e[0m");	break;
		case 13:	return ("\e[93mHIN\e[0m");		break;
		case 14:	return ("\e[93mUNKNOWN\e[0m");	break;
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

// void	ft_leaks(void)
// {
// 	system("leaks minishell");
// }

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
