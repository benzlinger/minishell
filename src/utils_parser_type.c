#include "../include/minishell.h"

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
	int	i;
	int	j;

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

/**
 * 	@brief	checks if typed-in command is valid
 * 	@param	s: pointer to literal token string of type COMMAND
 * 	@return path to the command e.g. "/bin/ls"
 * 		NULL if no command found
 */
char	*type_command(char **s)
{
	char	*tmp;
	char	*path;

	tmp = ft_strdup("/bin/");
	path = ft_strjoin(tmp, *s);
	free(tmp);
	if (access(path, F_OK) != 0)
	{
		ft_parse_error(*s, ": command not found");
		free(*s);
		free(path);
		return (NULL);
	}
	return (path);
}
