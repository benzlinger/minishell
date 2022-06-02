/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btenzlin <btenzlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:11:19 by rsiebert          #+#    #+#             */
/*   Updated: 2022/06/02 10:57:54 by btenzlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * 	@brief	only function that should exit the programm
 * 		is making sure that the programm exits cleanly
 * 	@param	err_code: code for exit to execute on later
 */
void	ft_exit(int err_code)
{
	exit(err_code);
}

void	ft_exit_eof(int err_code)
{
	printf("\033[1A");
	rl_on_new_line();
	rl_redisplay();
	write(1, "exit\n", 5);
	err_code = 0;
	ft_exit(g_exitstatus);
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

int	ft_exec_error(char *err_msg1, t_data *data)
{
	write(2, ERROR, ft_strlen(ERROR));
	write(2, err_msg1, ft_strlen(err_msg1));
	write(2, "\n", 1);
	if (data)
		g_exitstatus = EXIT_FAILURE;
	return (EXIT_FAILURE);
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
