#include "../include/minishell.h"

/**
 * 	@brief	check for quotes, brackets and stuff
 * 	@param	c: a single char
 * 	@return true if char is quote or bracket etc.
 */
static bool	ft_check_quote(char c, char *q)
{
	if (q == NULL)
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
	else
	{
		if (c == *q)
			return (true);
		else
			return (false);
	}
}

static void	ft_increment(int *i, int *j)
{
	*i += 1;
	*j += 1;
}

/**
 * 	@brief	changes the delimiter from the string from ' ' to ','
 * 	@param	pline: promptline from readline
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
