#include "../include/minishell.h"

/**
 * 	@brief	recode of linux echo function
 *	@param	command line from parser
 *	@return	if function succeeded
 *	UNCLEAR	do backslash sequences have to be handled (without -e flag)?
 */
int	ft_echo(char **cmd_line, int fd)
{
	int	i;
	int	is_flag;

	if (!cmd_line[1])
	{
		write(fd, "\n", 1);
		return (EXIT_SUCCESS);
	}
	is_flag = 0;
	i = 1;
	while (cmd_line[i] && !ft_strncmp(cmd_line[i], "-n", 2))
	{
		is_flag = 1;
		i++;
	}
	while (cmd_line[i])
	{
		write(fd, cmd_line[i], ft_strlen(cmd_line[i]));
		if (cmd_line[i + 1])
			write(fd, " ", 1);
		i++;
	}
	if (!is_flag)
		write(fd, "\n", 1);
	return (EXIT_SUCCESS);
}

/**	@brief	changes current working directory of the shell
 *	@param	command line from parser
 *	@return	if function scceeded
 */
int	ft_cd(char **cmd_line)
{
	int		ret;
	char	*homedir;
	char	*path;
	char	*new_path;

	if (!cmd_line)
		return (EXIT_FAILURE);
	if (cmd_line[1] && cmd_line[1][0] == '~')
	{
		homedir = "/Users/btenzlin";
		path = ft_substr(cmd_line[1], 1, ft_strlen(cmd_line[1]));
		new_path = ft_strjoin(homedir, path, NULL);
		free(path);
		ret = chdir(new_path);
		free(new_path);
	}
	else if (!cmd_line[1])
		ret = chdir("/Users/btenzlin");
	else
		ret = chdir(cmd_line[1]);
	if (ret == -1)
	{
		ft_exec_error(strerror(errno), NULL);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/**	@brief	print name of the working directory
 *	@return	if function succeeded
 */
int	ft_pwd(char **cmd_line, int fd)
{
	char	*path;

	if (cmd_line[1])
	{
		ft_exec_error("pwd: no flags or arguments supported.", NULL);
		return (EXIT_FAILURE);
	}
	path = getcwd(NULL, 0);
	if (!path)
		ft_error(strerror(errno));
	write(fd, path, ft_strlen(path));
	write(fd, "\n", 1);
	free(path);
	return (EXIT_SUCCESS);
}

/**	@brief	print list of environment variables
 *	@param	head of env list
 *	@return	if function succeeded
 */
int	ft_env(t_data *data, char **cmd_line, int fd)
{
	t_vars	*tmp;

	if (!data->vars)
		return (EXIT_FAILURE);
	if (cmd_line[1])
	{
		ft_exec_error("env: no flags or arguments supported.", NULL);
		return (EXIT_FAILURE);
	}
	tmp = data->vars;
	while (tmp)
	{
		if (tmp->value)
		{
			write(fd, tmp->name, ft_strlen(tmp->name));
			write(fd, "=", 1);
			write(fd, tmp->value, ft_strlen(tmp->value));
			write(fd, "\n", 1);
		}
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
