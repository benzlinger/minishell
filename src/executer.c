#include "../include/minishell.h"

static char	**export_cmd(char *cmd)
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
			ex_cmd[j] = ',';
			j++;
		}
		ex_cmd[j] = cmd[i];
		i++;
		j++;
	}
	ex_cmd[j] = '\0';
	ex_array = ft_split(ex_cmd, ',');
	free(ex_cmd);
	return (ex_array);
}

/**	@brief	execute binary commands
 *	-> forks a child to execute (parent waits for child)
 *	@param	command line
 *	@return	if function succeeded
 */
static int	exec_not_builtin(char **cmd_line, t_data *data)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		execve(cmd_line[0], cmd_line, data->env_list);
		ft_error(strerror(errno));
	}
	else if (pid < 0)
		ft_error(strerror(errno));
	else
	{
		wait(&status);
		data->exitstatus = status % 255;
	}
	return (0);
}

/**	@brief	execute builtin commands
 *	@param	command line (needs to be split)
 *	@return	if function succeeded
 */
int	msh_executer(t_data *data)
{
	int		status;
	char	**cmd_line;
	char	**exp_cmd;

	status = 1;
	cmd_line = ft_split(data->command, ',');
	if (!ft_strncmp(cmd_line[0], "echo", 4))
		data->exitstatus = ft_echo(cmd_line);
	else if (!ft_strncmp(cmd_line[0], "pwd", 3))
		data->exitstatus = ft_pwd();
	else if (!ft_strncmp(cmd_line[0], "cd", 2))
		data->exitstatus = ft_cd(cmd_line);
	else if (!ft_strncmp(cmd_line[0], "env", 3))
		data->exitstatus = ft_env(data->vars);
	else if (!ft_strncmp(cmd_line[0], "export", 6))
	{
		exp_cmd = export_cmd(data->command);
		ft_export(data, exp_cmd);
		free_2d_array(exp_cmd);
	}
	else if (!ft_strncmp(cmd_line[0], "unset", 5))
	{
		exp_cmd = export_cmd(data->command);
		data->vars = ft_unset(exp_cmd, data);
		free_2d_array(exp_cmd);
	}
	else if (!ft_strncmp(cmd_line[0], "exit", 4))
	{
		write(1, "exit\n", 5);
		status = 0;
	}
	else
		exec_not_builtin(cmd_line, data);
	free_2d_array(cmd_line);
	return (status);
}
