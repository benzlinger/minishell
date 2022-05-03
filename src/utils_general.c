#include "../include/minishell.h"

char	*ft_color_format_str(char *s, char *pre, char **tofree)
{
	char	*suf;
	char	*out;
	int		i;
	int		j;

	suf = ft_strdup("\e[0m");
	i = ft_strlen(s) + ft_strlen(pre) + ft_strlen(suf);
	out = ft_calloc(i + 1, sizeof(char));
	if (out == NULL)
		ft_error(strerror(errno));
	i = 0;
	j = 0;
	while (pre[i])
	{
		out[j] = pre[i];
		i++;
		j++;
	}
	i = 0;
	while (s[i])
	{
		out[j] = s[i];
		i++;
		j++;
	}
	i = 0;
	while (suf[i])
	{
		out[j] = suf[i];
		i++;
		j++;
	}
	if (tofree != NULL)
		free(*tofree);
	free(suf);
	return (out);
}
