#include "../include/minishell.h"

/*	writes an error message to the stderr and exits program
 *	@param status: error code for corresponding error message
 *	@return same error code gets return in exit()
 */
int	ft_error(int status)
{
	if (status == ALLOC)
		write(2, ERROR"A dynamic memory allocation failed.", 42);
	exit(status);
}
