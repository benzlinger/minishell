#include "../include/minishell.h"

/**
 * 	@brief	figures out the classification of a token
 *	@param	literal: literal (token)string of command prompt
 *	@return	enumarated clasification (int)
 * 	@prtype	int ft_get_type(char *literal);
 */

/**
 * 	@brief	checks for EOF "signal" from ctrl+D and
 * 		exits the programm if an EOF was detected
 * 		also check if string is only space ' '
 * 	@param	s: string from readline
 * 	@return	true is returned if s is not NULL (no EOF detected)
 * 		true if string is not only space ' '
 */
bool	ft_check_EOF(char *s)
{
	int	i;

	if (s == NULL)
		ft_exit(EOF);
	i = 0;
	while (s[i])
	{
		if (s[i] != ' ')
			return (true);
		i++;
	}
	return (false);
}

/**
 * 	@brief	gets the pipe_index for the tokens starting by 0
 *		first occuring pipe also gets pipe_index == 0
 *		second one gets pipe_index == 1 etc.
 *	@param	prompt:	command line prompt
 *	@param	pos: index of token in command line prompt (position)
 *	@return	the pipe_index
 */
int	ft_get_pipe_index(char **prompt, int pos)
{
	int	i;
	int	pipe_count;

	i = 0;
	pipe_count = 0;
	while (i < pos)
	{
		if (prompt[i][0] == '|' && prompt[i][1] == '\0')
			pipe_count++;
		i++;
	}
	return (pipe_count);
}
