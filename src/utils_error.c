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
	// free_vars(data->vars);
	exit(err_code);
}

/**	
 * 	@brief	writes an error message and returns NULL
 * 		is able to print two error messages
 *	@param	err_msg1: string error message
 *	@param	err_msg2: second string error message, set NULL if not needed
 *	@return NULL
 */
char	*ft_parse_error(char *err_msg1, char *err_msg2)
{
	write(2, ERROR, ft_strlen(ERROR));
	write(2, err_msg1, ft_strlen(err_msg1));
	if (err_msg2 != NULL)
		write(2, err_msg2, ft_strlen(err_msg2));
	write(2, "\n", 1);
	return (NULL);
}

void	ft_exec_error(char *err_msg1, t_data *data)
{
	write(2, ERROR, ft_strlen(ERROR));
	write(2, err_msg1, ft_strlen(err_msg1));
	write(2, "\n", 1);
	if (data)
		data->exitstatus = EXIT_FAILURE;
}

/**	
 * 	@brief	writes an error message to the stderr and exits program
 *	@param	err_msg1: string error message
 */
void	ft_error(char *err_msg)
{
	write(2, ERROR, ft_strlen(ERROR));
	write(2, err_msg, ft_strlen(err_msg));
	write(2, "\n", 1);
	ft_exit(EXIT_FAILURE);
}
