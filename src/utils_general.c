#include "../include/minishell.h"

char	*find_env_var_value(t_data *data, char *name)
{
	t_vars	*current;

	current = data->vars;
	while (current)
	{
		if (!ft_strncmp(current->name, name, ft_strlen(name) + 1)
			&& current->value)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

/**	@brief	parse commandline for export and unset (special case with = symbol)
 *	@param	cmd command line
 *	@return	command line for export and unset
 */
char	**export_cmd(char *cmd)
{
	char	*ex_cmd;
	char	**ex_array;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ex_cmd = malloc(ft_strlen(cmd) + 2);
	if (!ex_cmd)
		ft_error(strerror(errno));
	while (cmd[i])
	{
		if (cmd[i] == '=')
		{
			ex_cmd[j] = 31;
			j++;
		}
		ex_cmd[j] = cmd[i];
		i++;
		j++;
	}
	ex_cmd[j] = '\0';
	ex_array = ft_split(ex_cmd, 31);
	free(ex_cmd);
	return (ex_array);
}

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
