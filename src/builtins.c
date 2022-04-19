#include "../include/minishell.h"

//	prob need struct vor env variables (in main oder msh_loop)
//	otherwise won't be saved for next commands

//	do we want to include function name in command line argument
//	e.g. from parser to echo: "echo -n hello world" or 
//	"-n hello world"?

//	confusing how failure==1 and success==0

//	NEEDS CLEANUP: how do we want to do file management
//	need to add bultins.c + export.c to makefile

// check docs

/*	@brief	get size of 2d array
 *	@params	2d array
 *	@return	size of array
 */
static int	get_size_2d(char **arr)
{
	int	i;

	if (!arr)
		return (0);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}

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
	if (!cmd_line[1])
	{
		printf("\n");
		return (EXIT_SUCCESS);
	}
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
 *	@params	command line from parser
 *	@return	if function scceeded
 *	FIXME	is error handling wrong? get undefined error: 0
 */
int	ft_cd(char **cmd_line)
{
	char	*buf;
	int		ret;

	if (!cmd_line)
		return (EXIT_FAILURE);
	if (!cmd_line[1])
	{
		chdir("/Users/btenzlin");
		printf("%s\n", strerror(errno)); //ask
	}
	else
	{
		chdir(cmd_line[1]);
		printf("%s\n", strerror(errno)); //ask
	}
	return (EXIT_SUCCESS);
}

/*	@brief	print name of the working directory
 *	@return	if function succeeded
 *	DECIDE	if we want to use set size array or
 *				dinamically allocate memory for path
 */
int	ft_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	printf("%s\n", strerror(errno)); //ask
	if (!path)
		return (EXIT_FAILURE);
	printf("%s\n", path);
	free(path);
	return (EXIT_SUCCESS);
}

/*	@brief	print list of environment variables
 *	@return	if function succeeded
 *	TODO:	find way to get *envp[] from main to executer (struct possibly)
 */
int	ft_env(char	**env)
{
	int	i;

	if (!env)
		return (EXIT_FAILURE);
	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
