#include "../include/minishell.h"

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

/**
 * 	@brief	recode of linux echo function
 *	@param	command line from parser
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
	while (!ft_strncmp(cmd_line[i], "-n", 2))
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
	int	ret;

	if (!cmd_line)
		return (EXIT_FAILURE);
	if (!cmd_line[1])
		ret = chdir("/Users/btenzlin");
	else
		ret = chdir(cmd_line[1]);
	if (ret)
	{
		printf("%s\n", strerror(errno));
		return (EXIT_FAILURE);
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
	if (!path)
		ft_error(strerror(errno));
	printf("%s\n", path);
	free(path);
	return (EXIT_SUCCESS);
}

/*	@brief	print list of environment variables
 *	@return	if function succeeded
 */
int	ft_env(char	**env_list)
{
	int	i;

	if (!env_list)
		return (EXIT_FAILURE);
	i = 0;
	while (env_list[i])
	{
		printf("%s\n", env_list[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
