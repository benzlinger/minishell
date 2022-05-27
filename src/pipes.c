#include "../include/minishell.h"

static char	**get_cmd_array(t_data *data)
{
	char			**cmd_array;
	t_token_list	*tmp;
	int				i;
	int				size;

	tmp = data->tokens;
	size = 0;
	while (tmp)
	{
		if (tmp->type == PIPE)
			size++;
		tmp = tmp->next;
	}
	cmd_array = malloc(sizeof(char *) * size + 2);
	if (!cmd_array)
		ft_error(strerror(errno));
	i = 0;
	while (cmd_array[i])
	{
		cmd_array[i] = NULL;
		i++;
	}
	i = 0;
	tmp = data->tokens;
	while (i <= size && tmp)
	{
		if (tmp->type == PIPE)
		{
			tmp = tmp->next;
			i++;
		}
		else
			cmd_array[i] = my_strjoin(cmd_array[i], tmp->token);
		tmp = tmp->next;
	}
	cmd_array[i] = NULL;
	return (cmd_array);
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
			cmds[j] = ft_split(cmd_array[j], 31);
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
		msh_executer(data, cmds[i]);
		close(data->fd[1]);
	}
	else //last pipe (end of command)
	{
		close(data->fd[0]);
		close(data->fd[1]);
		dup2(*myfd, STDIN_FILENO);
		msh_executer(data, cmds[i]);
	}
	exit(data->exitstatus);
}

/**	@brief	waits for child, gets exit status
 *	@param	pid pid
 *	@return	exit status of child
 */
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

/**	@brief	checks if cmd line has pipe (not in quotes)
 *	@param	data data struct
 *	@return	if pipe exists
 */
static int	has_pipe(t_data *data)
{
	t_token_list	*tmp;

	if (!data->tokens)
		return (0);
	tmp = data->tokens;
	while (tmp)
	{
		if (tmp->type == PIPE)
			return (1);
		tmp = tmp->next;
	}
	return (0);
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
	char	**test;

	if (has_pipe(data))
	{
		// test = get_cmd_array(data);
		// print_2d_array(test);
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
