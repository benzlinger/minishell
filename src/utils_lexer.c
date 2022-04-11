#include "../include/minishell.h"

/**
 * 	@brief	check for quotes, brackets and stuff
 * 	@param	c: a single char
 * 	@return true if char is quote or bracket etc.
 */
static bool	ft_check_for_quote(char c)
{
	if (c == '"' || c == 39) //ascii code for ' is 39, just in case
		return (true);
	else if (c == '(' || c == '{' || c == '[')
		return (true);
	else if (c == ')' || c == '}' || c == ']')
		return (true);
	else
		return (false);
}

/**
 * 	@brief	changes the delimiter from the string from ' ' to ','
 * 	@param	pline: promptline from readline
 * 	@return	dline: delimited promptline with ',' instead of ' '
 * 		except in "...", (...), {...}, [...], '...'
 * 	@ERROR	takes strings like "hello) or [world} as acceptable tokens
 */
char	*ft_delimit_line(char *pline)
{
	char	*dline;
	int	i;
	int	j;

	dline = ft_calloc(ft_strlen(pline) + 1, sizeof(char));
	if (dline == NULL)
		ft_error(strerror(errno));
	i = 0;
	j = 0;
	while (pline[i])
	{
		if (ft_check_for_quote(pline[i]))
		{
			dline[j] = pline[i];
			i++;
			j++;
			while (!(ft_check_for_quote(pline[i])) && pline[i])
			{
				dline[j] = pline[i];
				i++;
				j++;
			}
			dline[j] = pline[i];
			i++;
			j++;
		}
		else
		{
			if (pline[i] == ' ')
				dline[j] = ',';
			else
				dline[j] = pline[i];
			i++;
			j++;
		}
	}
	return (dline);
}

/**
 * 	@brief	checks for EOF "signal" from ctrl+D and
 * 		exits the programm if an EOF was detected
 * 	@param	s: string from readline
 * 	@return	true is returned if s is not NULL (no EOF detected)
 */
bool	ft_check_EOF(char *s)
{
	if (s == NULL)
		ft_exit(EOF);
	return (true);
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
