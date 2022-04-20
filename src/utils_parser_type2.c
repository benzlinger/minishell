#include "../include/minishell.h"

/**
 * 	ATTENTION!
 * 	This file handels double quotes but is not bug free and has norm issues.
 *
 * 	Known bugs:
 *	-> double quotes are not removed
 *	-> echo hello world -> is: ERROR -> should: hello world
 *	-> echo hello$USER -> is: ERROR -> should: hellorsiebert
 *	-> echo hello$UNKOWNVAR -> is: ERROR -> should: hello
 *	-> echo hello$UNKOWNVAR bye -> is: ERROR -> should: hello bye
 *	
 *	Due to a lot of missing stuff and huge norm issues I will
 *	rewrite this entire file at some point
 */

static char	*get_envar_name(char *s)
{
	char	*envar;
	int	i;
	int	j;
	int	k;

	i = 0;
	while (s[i] != '$')
		i++;
	j = 0;
	while (s[i] != ' ' && s[i] != '"' && s[i] && ++i)
		j++;
	envar = ft_calloc(j + 1, sizeof(char));
	if (envar == NULL)
		return (ft_parse_error(strerror(errno), NULL));
	i = (i - j) + 1;
	if (ft_check_quote(s[i], NULL) && ++i)
		j -= 2;
	k = 0;
	while (--j > 0)
	{
		envar[k] = s[i];
		k++;
		i++;
	}
	return (envar);
}

static char	*remove_quotes(char *s)
{
	char	*out;
	size_t	i;
	int	j;

	out = ft_calloc(ft_strlen(s), sizeof(char));
	if (out == NULL)
		return (ft_parse_error(strerror(errno), NULL));
	i = 0;
	j = 1;
	while (i < ft_strlen(s) - 2)
	{
		out[i] = s[j];
		i++;
		j++;
	}
	return (out);
}

static bool	envar_exists(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
			return (true);
		i++;
	}
	return (false);
}

static char	*insert_envar_value(char *s, char *envar_name)
{
	char	*envar_value;
	char	*out;
	char	*tmp;
	int	i;
	int	j;
	char	*tmp2;

	envar_value = getenv(envar_name);
	if (envar_value == NULL)
		return (ft_parse_error(envar_name, ": variable not found"));
	tmp = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (tmp == NULL)
		return (ft_parse_error(strerror(errno), NULL));
	i = 0;
	while (s[i] != '$')
	{
		tmp[i] = s[i];
		i++;
	}
	tmp2 = ft_strjoin(tmp, envar_value);
	i = 0;
	while (s[i] != '$')
		i++;
	i += ft_strlen(envar_name);
	if (ft_check_quote(s[i + 2], NULL))
		i += 2;
	j = 0;
	ft_bzero(tmp, ft_strlen(tmp));
	while (s[i] && ++i)
	{
		tmp[j] = s[i];
		j++;
	}
	out = ft_strjoin(tmp2, tmp);
	free(tmp);
	free(tmp2);
	return (out);
}

char	*type_dquote(char **s)
{
	char	*out;
	char	*envar_name;
	char	*tmp;

	if (envar_exists(*s) == false)
	{
		out = remove_quotes(*s);
		envar_name = NULL;
	}
	else
	{
		envar_name = get_envar_name(*s);
		out = insert_envar_value(*s, envar_name);
		while (envar_exists(out) && (tmp = ft_strdup(out)))
		{
			free(envar_name);
			envar_name = get_envar_name(out);
			free(out);
			out = insert_envar_value(tmp, envar_name);
			free(tmp);
		}
	}
	free(envar_name);
	if (out == NULL)
		return (NULL);
	free(*s);
	return (out);
}
