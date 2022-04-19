#include "../include/minishell.h"

//TIP	use command $> type [command-name]
//		-> to check if command is builtin or binary

/*	@brief	free 2 dimensional array and its contents
 *	@params	array to free
 */
static void	free_2d_array(char **arr)
{
	int	i;

	if (arr)
	{
		i = 0;
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
		free(arr);
	}
}

/*	@brief	execute binary commands
 *	-> forks a child to execute (parent waits for child)
 *	@params	command line
 *	@return	if function succeeded
 */
static int	exec_not_builtin(char **cmd_line)
{
	pid_t	pid;
	int		status;
	char	*cmd;

	pid = fork();
	if (pid == 0)
	{
		cmd = ft_strjoin("/bin/", cmd_line[0]);
		execve(cmd, cmd_line, NULL);
		// execvp(cmd_line[0], cmd_line); //FORBIDDEN FUNC: just for testing
		printf("%s\n", strerror(errno)); //ask
		free(cmd);
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
		write(2, "Error\n", 6);
	else
		wait(&status);
	return (0);
}

/*	@brief	execute builtin commands
 *	@params	command line (needs to be split)
 *	@return	if function succeeded
 */
int	msh_executer(char *command)
{
	int		status;
	char	**cmd_line;

	// status = printf("%s\n", command);
	cmd_line = ft_split(command, ',');
	if (!ft_strncmp(cmd_line[0], "echo", 4))
		ft_echo(cmd_line);
	else if (!ft_strncmp(cmd_line[0], "pwd", 3))
		ft_pwd();
	else if (!ft_strncmp(cmd_line[0], "cd", 2))
		ft_cd(cmd_line); //FYI changed to 2d array
	else if (!ft_strncmp(cmd_line[0], "exit", 4))
	{
		write(1, "exit\n", 5);
		return (0); //does 0-status exit properly?
	}
	else
		exec_not_builtin(cmd_line);
	status = 1;
	free_2d_array(cmd_line);
	return (status);
}
