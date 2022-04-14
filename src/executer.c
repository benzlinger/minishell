#include "../include/minishell.h"

static int	exec_not_builtin(char **cmd_line)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		execvp(cmd_line[0], cmd_line); //FORBIDDEN FUNC: just for testing
		// execve(cmd_line[0], cmd_line, NULL);
		printf("%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
		write(2, "Error\n", 6);
	else
		wait(&status);
	return (0);
}

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
		ft_cd(command);
	else if (!ft_strncmp(cmd_line[0], "exit", 4))
	{
		write(1, "exit\n", 5);
		return (0);
	}
	else
	{
		exec_not_builtin(cmd_line);
	}
	status = 1;
	return (status);
}
