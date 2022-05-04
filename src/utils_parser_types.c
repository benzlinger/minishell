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
	{
		if (s[0] == '<' && s[1] == '<')
			return (EXIT_SUCCESS);
		else if (s[0] == '>' && s[1] == '>')
			return (EXIT_SUCCESS);
	}
	ft_parse_error(s, ": invalid redirection syntax");
	return (EXIT_FAILURE);
}

/**
 * 	@brief	removes single quotes
 * 	@param	pointer to literal token string of type SQUOTE
 * 	@return	string without singlequotes
 * 	@NOTE	Very little testing was done
 * 		also I'm not entirly sure if removing the single quotes was
 * 		all that needed to be done
 */
char	*type_squote(char **s)
{
	char	*out;
	int		i;
	int		j;

	out = ft_calloc(ft_strlen(*s) + 1, sizeof(char));
	if (out == NULL)
		ft_error(strerror(errno));
	i = 0;
	j = 1;
	while (s[0][j] != 39 && s[0][j])
	{
		out[i] = s[0][j];
		i++;
		j++;
	}
	free(*s);
	return (out);
}

/**
 * 	@brief	converts var name into var value
 * 	@param	pointer to literal token string of type ENVAR
 * 	@return	envar: either the converted var value
 * 		or envar set to NULL if no var found
 */
char	*type_envar(char **s)
{
	char	*envar;
	char	*name;
	int		i;
	int		j;

	name = ft_calloc(ft_strlen(*s) + 1, sizeof(char));
	if (name == NULL)
		ft_error(strerror(errno));
	i = 0;
	while (s[0][i] == '$' || ft_check_quote(s[0][i], NULL))
		i++;
	j = 0;
	while (ft_check_quote(s[0][i], NULL) == false && s[0][i])
	{
		name[j] = s[0][i];
		i++;
		j++;
	}
	envar = getenv(name);
	if (envar == NULL)
		ft_parse_error(name, ": variable not found");
	free(*s);
	free(name);
	return (envar);
}
