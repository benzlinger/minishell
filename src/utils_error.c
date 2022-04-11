#include "../include/minishell.h"

/**
 * 	@brief	only function that should exit the programm
 * 		is making sure that the programm exits cleanly
 * 	@param	err_code: code for exit to execute on later
 */
void	ft_exit(int err_code)
{
	//system("leaks minishell");
	// TODO freeing before exit function for clean shutdown
	exit(err_code);
}

/**	
 * 	@brief	writes an error message to the stderr and exits program
 *	@param	err_msg: string error message
 */
void	ft_error(char *err_msg)
{
	write(2, ERROR, ft_strlen(ERROR));
	write(2, err_msg, ft_strlen(err_msg));
	write(2, "\n", 1);
	ft_exit(EXIT_FAILURE);
}
