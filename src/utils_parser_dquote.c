#include "../include/minishell.h"

// FIXME $> "echo" works for some reason

bool	envar_exists(char *s)
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

char	*type_dquote(char **s)
{
	char	*out;

	out = handle_quotes(*s);
	if (out == NULL)
	{
		free(*s);
		return (NULL);
	}
	if (envar_exists(*s))
		out = insert_envar(&out);
	if (out == NULL)
		return (NULL);
	free(*s);
	return (out);
}
