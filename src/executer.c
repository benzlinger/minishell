#include "../include/minishell.h"

//TIP	use command $> type [command-name]
//		-> to check if command is builtin or binary

static char	**export_cmd(char *cmd)
{
	char	*ex_cmd;
	char	**ex_array;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ex_cmd = malloc(ft_strlen(cmd) + 2);
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

/*	@brief	execute binary commands
 *	-> forks a child to execute (parent waits for child)
 *	@params	command line
 *	@return	if function succeeded
 */
static int	exec_not_builtin(char **cmd_line, char **env_list)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		execve(cmd_line[0], cmd_line, env_list);
		// execvp(cmd_line[0], cmd_line); //FORBIDDEN FUNC: just for testing
		printf("%s\n", strerror(errno));
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
int	msh_executer(t_data *data)
{
	int		status;
	char	**cmd_line;
	char	**exp_cmd;

	cmd_line = ft_split(data->command, ',');
	if (!ft_strncmp(cmd_line[0], "echo", 4))
		ft_echo(cmd_line);
	else if (!ft_strncmp(cmd_line[0], "pwd", 3))
		ft_pwd();
	else if (!ft_strncmp(cmd_line[0], "cd", 2))
		ft_cd(cmd_line);
	else if (!ft_strncmp(cmd_line[0], "env", 3))
		ft_env(data->env_list);
	else if (!ft_strncmp(cmd_line[0], "export", 6))
	{
		exp_cmd = export_cmd(data->command);
		data->vars = ft_export(exp_cmd, data->vars, data->env_list);
		free_2d_array(exp_cmd);
	}
	else if (!ft_strncmp(cmd_line[0], "exit", 4))
	{
		write(1, "exit\n", 5);
		return (0); //does 0-status exit properly?
	}
	else
		exec_not_builtin(cmd_line, data->env_list);
	status = 1;
	free_2d_array(cmd_line);
	return (status);
}
