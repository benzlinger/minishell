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

/**	@brief	execute binary commands
 *	-> forks a child to execute (parent waits for child)
 *	@param	cmd_line command line
 *	@param	data data stuct with env vars and exitstatus
 *	@return	if function succeeded
 */
static int	exec_not_builtin(char **cmd_line, t_data *data)
{
	pid_t	pid;
	char	**new_cmd_line;

	new_cmd_line = NULL;
	// FIXME doesn't new_cmd_line need to be freed? (doesn't leak because in child --> no malloc in parent)
	// -> maybe bad practice?
	pid = fork();
	if (pid == -1)
		ft_error(strerror(errno));
	if (pid == 0)
	{
		if (redirec_in(cmd_line))
		{
			new_cmd_line = ft_redirec(cmd_line, data);
			execve(cmd_line[0], new_cmd_line, data->env_list);
		}
		else
			execve(cmd_line[0], cmd_line, data->env_list);
		ft_error(strerror(errno));
	}
	else
		data->exitstatus = ft_wait(pid);
	return (data->exitstatus);
}

/**	@brief	parse command for executer without pipes
 *	@param	data datastruct
 *	@return	status for msh_loop
 */
// int	exec_nopipe(t_data *data)
// {
// 	char	**cmd_line;

// 	if (!ft_strncmp(data->command, "export", 6)
// 		|| !ft_strncmp(data->command, "unset", 5))
// 		cmd_line = export_cmd(data->command);
// 	else
// 		cmd_line = ft_split(data->command, ',');
// 	data->status = 1;
// 	if (check_builtins(cmd_line[0]))
// 		data->exitstatus = msh_executer(data, cmd_line);
// 	else
// 	{
// 		data->pid = fork();
// 		if (data->pid == -1)
// 			ft_error(strerror(errno));
// 		if (data->pid == 0)
// 			exit(msh_executer(data, cmd_line));
// 		else
// 			data->exitstatus = ft_wait(data->pid);
// 	}
// 	// data->exitstatus = msh_executer(data, cmd_line);
// 	free_2d_array(cmd_line);
// 	return (data->status);
// }

int	exec_nopipe(t_data *data)
{
	char	**cmd_line;

	if (!ft_strncmp(data->command, "export", 6)
		|| !ft_strncmp(data->command, "unset", 5))
		cmd_line = export_cmd(data->command);
	else
		cmd_line = ft_split(data->command, 31);
	data->status = 1;
	msh_executer(data, cmd_line);
	free_2d_array(cmd_line);
	return (data->status);
}

static void	msh_executer_two(t_data *data, char **cmd_line)
{
	char	**builtin_cmd_line;
	char	*tmp;

	data->builtin_fd = get_builtin_fd(data);
	tmp = remove_redirec(cmd_line);
	builtin_cmd_line = ft_split(tmp, 31);
	if (!ft_strncmp(cmd_line[0], "echo", 4))
		data->exitstatus = ft_echo(builtin_cmd_line, data->builtin_fd);
	else if (!ft_strncmp(cmd_line[0], "pwd", 3))
		data->exitstatus = ft_pwd(builtin_cmd_line, data->builtin_fd);
	else if (!ft_strncmp(cmd_line[0], "cd", 2))
		data->exitstatus = ft_cd(cmd_line);
	else if (!ft_strncmp(cmd_line[0], "env", 3))
		data->exitstatus = ft_env(data, builtin_cmd_line, data->builtin_fd);
	else if (!ft_strncmp(cmd_line[0], "export", 6))
		ft_export(data, builtin_cmd_line, data->builtin_fd);
	else if (!ft_strncmp(cmd_line[0], "unset", 5))
		data->vars = ft_unset(cmd_line, data);
	else if (!ft_strncmp(cmd_line[0], "exit", 4))
	{
		write(1, "exit\n", 5);
		data->status = 0;
	}
	free(tmp);
	free_2d_array(builtin_cmd_line);
}

static void	msh_executer_three(t_data *data, char **cmd_line)
{
	int	fd;

	fd = STDOUT_FILENO;
	if (!ft_strncmp(cmd_line[0], "echo", 4))
		data->exitstatus = ft_echo(cmd_line, fd);
	else if (!ft_strncmp(cmd_line[0], "pwd", 3))
		data->exitstatus = ft_pwd(cmd_line, fd);
	else if (!ft_strncmp(cmd_line[0], "cd", 2))
		data->exitstatus = ft_cd(cmd_line);
	else if (!ft_strncmp(cmd_line[0], "env", 3))
		data->exitstatus = ft_env(data, cmd_line, fd);
	else if (!ft_strncmp(cmd_line[0], "export", 6))
		ft_export(data, cmd_line, fd);
	else if (!ft_strncmp(cmd_line[0], "unset", 5))
		data->vars = ft_unset(cmd_line, data);
	else if (!ft_strncmp(cmd_line[0], "exit", 4))
	{
		write(1, "exit\n", 5);
		data->status = 0;
	}
}

/**	@brief	execute builtin commands
 *	@param	data struct containing command and env vars
 *	@return	if function succeeded
 */
int	msh_executer(t_data *data, char **cmd_line)
{
	data->status = 1;
	data->builtin_fd = STDOUT_FILENO;
	if(check_builtins(cmd_line[0]) && redirec_in(cmd_line))
		msh_executer_two(data, cmd_line);
	else if (check_builtins(cmd_line[0]))
		msh_executer_three(data, cmd_line);
	else
		data->exitstatus = exec_not_builtin(cmd_line, data);
	if (data->builtin_fd != STDOUT_FILENO)
		close(data->builtin_fd);
	return (data->exitstatus);
}
