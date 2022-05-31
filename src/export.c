#include "../include/minishell.h"

static void	ft_one(char **name, char **value, char **cmd_line, int *j)
{
	int	i;

	i = *j;
	*name = ft_strdup(cmd_line[i]);
	*value = ft_substr(cmd_line[i + 1], 1, ft_strlen(cmd_line[i + 1]));
	*j += 1;
}

/**	@brief	show or create new env variable [with value]
 *	@param	data struct, command line
 *	UNCLEAR: should export test =value work?
 */
int	ft_export(t_data *data, char **cmd_line, int fd, int is_exit)
{
	int		i;
	char	*name;
	char	*value;

	if (!cmd_line[1])
		data->exitstatus = show_vars(data->vars, fd);
	i = 0;
	while (++i && cmd_line[i])
	{
		if (cmd_line[i][0] == '=' && ++is_exit)
			ft_exec_error("Not a valid identifier", data);
		else if (cmd_line[i + 1] && cmd_line[i + 1][0] == '=')
		{
			ft_one(&name, &value, cmd_line, &i);
			append_var(name, value, data->vars);
		}
		else
		{
			name = ft_strdup(cmd_line[i]);
			append_var(name, NULL, data->vars);
		}
		if (!is_exit)
			data->exitstatus = EXIT_SUCCESS;
	}
	return (data->exitstatus);
}
