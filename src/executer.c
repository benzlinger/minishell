#include "../include/minishell.h"

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
 *	@param	cmd_line command line
 *	@param	data data stuct with env vars and exitstatus
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
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			data->exitstatus = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			data->exitstatus = 130;
	}
	return (0);
}

/**	@brief	parse command for executer without pipes
 *	@param	data datastruct
 *	@return	status for msh_loop
 */
int	exec_nopipe(t_data *data)
{
	char	**cmd_line;

	if (!ft_strncmp(data->command, "export", 6)
		|| !ft_strncmp(data->command, "unset", 5))
		cmd_line = export_cmd(data->command);
	else
		cmd_line = ft_split(data->command, ',');
	return (msh_executer(data, cmd_line));
}

/**	@brief	execute builtin commands
 *	@param	data struct containing command and env vars
 *	@return	if function succeeded
 */
int	msh_executer(t_data *data, char **cmd_line)
{
	int		status;

	status = 1;
	if (!ft_strncmp(cmd_line[0], "echo", 4))
		data->exitstatus = ft_echo(cmd_line);
	else if (!ft_strncmp(cmd_line[0], "pwd", 3))
		data->exitstatus = ft_pwd(cmd_line);
	else if (!ft_strncmp(cmd_line[0], "cd", 2))
		data->exitstatus = ft_cd(cmd_line);
	else if (!ft_strncmp(cmd_line[0], "env", 3))
		data->exitstatus = ft_env(data, cmd_line);
	else if (!ft_strncmp(cmd_line[0], "export", 6))
		ft_export(data, cmd_line);
	else if (!ft_strncmp(cmd_line[0], "unset", 5))
		data->vars = ft_unset(cmd_line, data);
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
