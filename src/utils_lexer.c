#include "../include/minishell.h"

/*	gets the pipe_index for the tokens starting by 0
 *	first occuring pipe also gets pipe_index == 0
 *	seconde one gets pipe_index == 1 etc.
 *	@param prompt:	command line prompt
 *	@param pos:	index of token in command line prompt (position)
 *	@return the pipe_index
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
