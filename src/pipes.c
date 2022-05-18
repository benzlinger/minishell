#include "../include/minishell.h"

/**	@brief	check if command line contains pipes
 *	@param	cmd_line command line
 *	@return	1 if there are pipes, 0 if not
 */
static int	has_pipe(char *cmd_line)
{
	int	i;

	if (!cmd_line)
		return (0);
	i = 0;
	while (cmd_line[i])
	{
		if (cmd_line[i] == '|' && cmd_line[i + 1])
			return (1);
		i++;
	}
	return (0);
}

/**	@brief	parse commandline with pipes into seperate commands
 *	@param	cmd_line command line
 *	@return	3d array with commands
 */
static char	***get_cmds(char *cmd_line)
{
	char	**cmd_array;
	char	***cmds;
	int		i;
	int		j;

	cmd_array = ft_split(cmd_line, '|');
	if (!cmd_array)
		ft_error(strerror(errno));
	i = 0;
	while (cmd_array[i])
		i++;
	cmds = malloc(sizeof(char **) * i + 1);
	if (!cmds)
		ft_error(strerror(errno));
	j = 0;
	while (j < i)
	{
		if (!ft_strncmp(cmd_array[j], "export", 6)
			|| !ft_strncmp(cmd_array[j], "unset", 5))
			cmds[j] = export_cmd(cmd_array[j]);
		else
			cmds[j] = ft_split(cmd_array[j], ',');
		j++;
	}
	cmds[j] = NULL;
	free_2d_array(cmd_array);
	i = 0;
	return (cmds);
}

/**	@brief	redirecting output to next command after pipe
 * 			--> exits because its a child process
 *	@param	cmds 3d array containing all commands without pipes
 *	@param	data datastruct
 *	@param	myfd file descriptor to redirect to
 *	@param	i counter from pipe_exec
 */
static void	pipe_exec_helper(char ***cmds, t_data *data, int *myfd, int i)
{
	if (cmds[i + 1]) //first or middle pipe
	{
		close(data->fd[0]);
		dup2(*myfd, STDIN_FILENO);
		dup2(data->fd[1], STDOUT_FILENO);
		data->status = msh_executer(data, cmds[i]);
		close(data->fd[1]);
	}
	else //last pipe (end of command)
	{
		close(data->fd[0]);
		close(data->fd[1]);
		dup2(*myfd, STDIN_FILENO);
		data->status = msh_executer(data, cmds[i]);
	}
	exit(data->exitstatus);
}

int	ft_wait(int pid)
{
	int	status;
	int	exit;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		exit = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		exit = 130;
	return (exit);
}

/**	@brief	check for pipes, and redirects output before execution
 *	@param	data datastruct
 *	@return	status for msh_loop
 */
int	pipe_exec(t_data *data)
{
	char	***cmds;
	int		i;
	int		ret;
	int		myfd;

	if (has_pipe(data->command))
	{
		cmds = get_cmds(data->command);
		i = 0;
		myfd = 0;
		while (cmds[i])
		{
			if (pipe(data->fd) == -1)
				ft_error(strerror(errno));
			data->pid = fork();
			if (data->pid == -1)
				ft_error(strerror(errno));
			if (data->pid == 0)
			{
				pipe_exec_helper(cmds, data, &myfd, i);
				ft_error(strerror(errno));
			}
			else
			{
				data->current_pipe = i;
				data->exitstatus = ft_wait(data->pid);
				close(data->fd[1]);
				myfd = data->fd[0];
			}
			i++;
		}
		close(data->fd[0]);
		free_3d_array(cmds);
		ret = data->status;
	}
	else
		ret = exec_nopipe(data);
	return (ret);
}
