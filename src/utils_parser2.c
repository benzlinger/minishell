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
