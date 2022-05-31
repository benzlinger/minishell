#include "../include/minishell.h"

int	has_exitstatus(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == '$' && s[i + 1] == '?')
			return (1);
		i++;
	}
	return (0);
}

static void	ft_one(char *exit, char **new, int *i, int *j)
{
	int	k;

	k = 0;
	while (exit[k])
	{
		new[0][*j] = exit[k];
		*j += 1;
		k++;
	}
	*i += 2;
}

static char	*replace_helper(char *s, char *exit, int new_size)
{
	char	*new;
	int		i;
	int		j;

	new = malloc(new_size + 1);
	if (!new)
		ft_error(strerror(errno));
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '$' && s[i + 1] == '?')
			ft_one(exit, &new, &i, &j);
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

char	*replace_exitstatus(char *s)
{
	int		i;
	int		j;
	int		size;
	char	*exit;
	char	*new;

	exit = ft_itoa(g_exitstatus);
	size = ft_strlen(exit);
	i = 0;
	j = 0;
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
