#include "../include/minishell.h"

int	msh_executer(char *command)
{
	int	status;

	status = printf("%s\n", command);
	return (status);
}
