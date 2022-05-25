#include "../include/minishell.h"

static char	*ft_append(char **old, char *suf)
{
	char	*pre;
	int		i;
	int		j;

	pre = ft_calloc(ft_strlen(*old) + ft_strlen(suf) + 2, sizeof(char));//FIXME please
	if (pre == NULL)
		ft_error(strerror(errno));
	i = 0;
	j = 0;
	while (old[0][i])
	{
		pre[j] = old[0][i];
		i++;
		j++;
	}
	pre[j] = '\n';
	i = 0;
	while (suf[i])
	{
		j++;
		pre[j] = suf[i];
		i++;
	}
	free(*old);
	return (pre);
}

char	*type_heredoc(char **s, char *token)
{
	char	*out;
	char	*newline;

	out = NULL;
	while (true)
	{
		newline = readline("\e[93mheredoc> \e[0m");
		if (ft_strncmp(newline, token, ft_strlen(token) + 1) == 0)
			break ;
		if (newline == NULL)
			break ;
		if (out == NULL)
			out = ft_strdup(newline);
		else
			out = ft_append(&out, newline);
		free(newline);
		newline = NULL;
	}
	if (newline != NULL)
		free(newline);
	free(*s);
	return (out);
}
