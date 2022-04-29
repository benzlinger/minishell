#include "../include/minishell.h"

/**
 * 	@brief	check for quotes, brackets and stuff (NULL)
 * 		or checks if c and *q are the same
 * 	@param	c: a single char
 * 	@param	q: char pointer, contains either NULL or a quote
 * 	@return true if char is quote or bracket etc. (NULL)
 * 		or true if c == *q
 */
bool	ft_check_quote(char c, char *q)
{
	if (q == NULL)
	{
		if (c == '"' || c == 39)	// 39 == '
			return (true);
		else if (c == '(' || c == '{' || c == '[')
			return (true);
		else if (c == ')' || c == '}' || c == ']')
			return (true);
		else
			return (false);
	}
	else
	{
		if (c == *q)
			return (true);
		else
			return (false);
	}
}

/**
 * 	@brief	increments i and j in one line to save some lines (norm)
 */
static void	ft_increment(int *i, int *j)
{
	*i += 1;
	*j += 1;
}

/**
 * 	@brief	changes the delimiter from the string from ' ' to ','
 * 	@param	pline: promptline from readline
 * 	@param	i: index var (saving line for norm)
 * 	@param	j: index var (saving line for norm)
 * 	@return	dline: delimited promptline with ',' instead of ' '
 * 		except in "...", (...), {...}, [...], '...'
 * 	@ERROR	Norminette
 */
char	*ft_delimit_line(char *pline, int i, int j)
{
	char	*dline;
	char	qchar;

	dline = ft_calloc(ft_strlen(pline) + 1, sizeof(char));
	if (dline == NULL)
		ft_error(strerror(errno));
	while (pline[i])
	{
		if (ft_check_quote(pline[i], NULL))
		{
			qchar = pline[i];
			dline[j] = pline[i];
			ft_increment(&i, &j);
			while (!(ft_check_quote(pline[i], &qchar)) && pline[i])
			{
				dline[j] = pline[i];
				ft_increment(&i, &j);
			}
			if (pline[i])
			{
				dline[j] = pline[i];
				ft_increment(&i, &j);
			}
		}
		else
		{
			if (pline[i] == ' ')
				dline[j] = ',';
			else
				dline[j] = pline[i];
			ft_increment(&i, &j);
		}
	}
	return (dline);
}
