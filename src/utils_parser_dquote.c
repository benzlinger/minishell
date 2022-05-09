#include "../include/minishell.h"

/**
 * 	@brief	checks if an envar is in a string
 * 	@param	s: string to check for envar
 * 	@return	true: a envar
 * 			false: no envar
 */
bool	envar_exists(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$' && s[i + 1] != '?')
			return (true);
		i++;
	}
	return (false);
}

/**
 * 	@brief	removes quotes from string
 * 	@param	old: old string to remove quotes from
 * 	@param	new: new string without quotes
 * 	@return 1
 */
static int	remove_quotes(char *old, char *new)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (old[i])
	{
		while (old[i] == '"')
			i++;
		new[j] = old[i];
		i++;
		j++;
	}
	return (EXIT_SUCCESS);
}

/**
 * 	@brief	counts quotes in string
 * 	@param	s: string to handle
 * 	@return	double quotes count in string s
 */
static int	quote_count(char *s)
{
	int	i;
	int	dq_count;

	i = 0;
	dq_count = 0;
	while (s[i])
	{
		if (s[i] == '"')
			dq_count++;
		i++;
	}
	return (dq_count);
}

/**
 * 	@brief	handles double quotes; removes them and inserts envars
 * 	@param	s: literal token string
 * 	@return converted string
 */
static char	*handle_quotes(char *s)
{
	char	*out;

	out = ft_calloc(ft_strlen(s), sizeof(char));
	if (out == NULL)
		ft_error(strerror(errno));
	if (quote_count(s) % 2 != 0)
	{
		free(out);
		return (ft_parse_error("odd amount of double quotes", NULL));
	}
	if (remove_quotes(s, out) != 0)
		return (NULL);
	return (out);
}

static char	*replace_helper(char *s, char *exit, int new_size)
{
	char	*new;
	int		i;
	int		j;
	int		k;

	new = malloc(new_size + 1);
	if (!new)
		ft_error(strerror(errno));
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '$' && s[i + 1] == '?')
		{
			k = 0;
			while (exit[k])
			{
				new[j] = exit[k];
				j++;
				k++;
			}
			i += 2;
		}
		else
		{
			new[j] = s[i];
			i++;
			j++;
		}
	}
	new[j] = '\0';
	return (new);
}

static char	*replace_exitstatus(char *s, t_data *data)
{
	int		i;
	int		j;
	int		size;
	char	*exit;
	char	*new;

	if (!s)
		return (s);
	i = 0;
	j = 0;
	exit = ft_itoa(data->exitstatus);
	size = ft_strlen(exit);
	while (s[i])
	{
		if (s[i] == '$' && s[i + 1] == '?')
		{
			j += size;
			i++;
		}
		else
			j++;
		i++;
	}
	new = replace_helper(s, exit, j);
	free(exit);
	free(s);
	return (new);
}

/**
 * 	@brief	handles double quotes; removes them and inserts envars
 * 	@param	s: pointer to literal token string
 * 	@return converted string
 */
char	*type_dquote(char **s, t_data *data)
{
	char	*out;

	out = handle_quotes(*s);
	if (out == NULL)
	{
		free(*s);
		return (NULL);
	}
	out = replace_exitstatus(out, data);
	if (envar_exists(*s))
		out = insert_envar(&out, data);
	if (out == NULL)
		return (NULL);
	free(*s);
	return (out);
}
