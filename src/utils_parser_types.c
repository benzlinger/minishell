#include "../include/minishell.h"

/**
 * 	@brief	checks for valid pipe syntax
 * 	@param	literal token string of type REDIREC
 * 	@return	0 if syntax is valid
 * 		1 if not
 */
int	type_pipe(char *s)
{
	if (ft_strlen(s) != 1)
	{
		ft_parse_error(s, ": invalid pipe syntax");
		g_exitstatus = 258;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/**
 * 	@brief	checks for valid redirection syntax
 * 	@param	literal token string of type REDIREC
 * 	@return	0 if syntax is valid
 * 		1 if not
 */
int	type_redirec(char *s)
{
	if (ft_strlen(s) == 1)
		return (EXIT_SUCCESS);
	else if (ft_strlen(s) == 2)
		if (s[0] == '>' && s[1] == '>')
			return (EXIT_SUCCESS);
	ft_parse_error(s, ": invalid redirection syntax");
	g_exitstatus = 258;
	return (EXIT_FAILURE);
}

static int	remove_quotes(char *old, char *new)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (old[i])
	{
		while (old[i] == '\'')
			i++;
		if (old[i] == '|')
			new[j] = 26;
		else
			new[j] = old[i];
		i++;
		j++;
	}
	if (quote_count(new, '"') % 2 != 0)
	{
		ft_parse_error("odd amount of double quotes", NULL);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/**
 * 	@brief	removes single quotes
 * 	@param	pointer to literal token string of type SQUOTE
 * 	@return	string without singlequotes
 */
char	*type_squote(char **s)
{
	char	*out;

	if (quote_count(*s, '\'') % 2 != 0)
	{
		free(*s);
		return (ft_parse_error("odd amount of single quotes", NULL));
	}
	out = ft_calloc(ft_strlen(*s) + 1, sizeof(char));
	if (out == NULL)
		ft_error(strerror(errno));
	if (remove_quotes(*s, out) != 0)
	{
		free(*s);
		return (NULL);
	}
	free(*s);
	return (out);
}
