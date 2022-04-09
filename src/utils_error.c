#include "../include/minishell.h"

//	TODO function comment
void	ft_exit(int err_code)
{
	system("leaks minishell");
	// TODO freeing before exit function for clean shutdown
	exit(err_code);
}

//	TODO change function comment
/*	writes an error message to the stderr and exits program
 *	@param status: error code for corresponding error message
 *	@return same error code gets return in exit()
 */
void	ft_error(char *err_msg)
{
	write(2, ERROR, ft_strlen(ERROR));
	write(2, err_msg, ft_strlen(err_msg));
	write(2, "\n", 1);
	ft_exit(EXIT_FAILURE);
}
