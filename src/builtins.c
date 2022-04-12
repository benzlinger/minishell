#include "../include/minishell.h"

//	do we want to include function name in command line argument
//	e.g. from parser to echo: "echo -n hello world" or 
//	"-n hello world"?

/*	@brief	recode of linux echo function
 *	@params	command line from parser
 *	@return	if function succeeded
 *	UNCLEAR	do backslash sequences have to be handled (without -e flag)?
 */
int	ft_echo(char **cmd_line)
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

/*	@brief	changes current working directory of the shell
 *	@params	command line IF POSSIBLE as string (as opposed to 2d array)
 *	@return	if function scceeded
 *	FIXME test when parser ready
 */
int	ft_cd(char *cmd_line)
{
	return (chdir(cmd_line));
}

/*	@brief	print name of the working directory
 *	@return	if function scceeded
 *	DECIDE	if we want to use set size array or dinamically allocate memory for path
 */
int	ft_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		return (EXIT_FAILURE);
	printf("%s\n", path);
	free(path);
	return (EXIT_SUCCESS);
}
