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
		if (c == '"' || c == 39)
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

static void	ft_one(int *i, int *j, char **dline, char **pline)
{
	char	qchar;

	qchar = pline[0][*i];
	dline[0][*j] = pline[0][*i];
	*j += 1;
	*i += 1;
	while (!(ft_check_quote(pline[0][*i], &qchar)) && pline[0][*i])
	{
		dline[0][*j] = pline[0][*i];
		*j += 1;
		*i += 1;
	}
	if (pline[0][*i])
	{
		dline[0][*j] = pline[0][*i];
		*j += 1;
		*i += 1;
	}
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

	dline = ft_calloc(ft_strlen(pline) + 1, sizeof(char));
	if (dline == NULL)
		ft_error(strerror(errno));
	while (pline[i])
	{
		if (ft_check_quote(pline[i], NULL))
			ft_one(&i, &j, &dline, &pline);
		else
		{
			if (pline[i] == ' ')
				dline[j] = 31;
			else
				dline[j] = pline[i];
			i++;
			j++;
		}
	}
	return (dline);
}
