#include "../include/minishell.h"

int	msh_executer(char *command)
{
	int		status;
	char	**cmd_line;

	// status = printf("%s\n", command);
	cmd_line = ft_split(command, ',');
	ft_echo(cmd_line);
	status = 1;
	return (status);
}
