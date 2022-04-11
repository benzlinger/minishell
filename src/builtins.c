#include "../include/minishell.h"

int	echo(char **cmd_line)
{
	int	i;
	int	is_flag;

	if (!cmd_line)
		return (EXIT_FAILURE);
	is_flag = 0;
	i = 1;
	if (!ft_strncmp(cmd_line[i], "-n", 2))
	{
		is_flag = 1;
		i++;
	}
	while (cmd_line[i])
	{
		printf("%s", cmd_line[i]);
		if (cmd_line[i + 1])
			printf(" ");
		i++;
	}
	if (!is_flag)
		printf("\n");
	return (EXIT_SUCCESS);
}