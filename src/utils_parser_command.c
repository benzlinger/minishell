#include "../include/minishell.h"

/**
 * 	@brief	circles through $PATH and trys to find the command in
 * 			any of the paths
 * 	@param	paths: split 2d array of $PATH
 * 	@param	command: executable to search for
 * 	@return index number of 2d array
 * 			-1 if command is not found in any of the paths
 */
static int	find_right_path(char **paths, char *command)
{
	int		i;
	char	*full_path;

	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], command, NULL);
		if (access(full_path, F_OK) == 0)
		{
			free(full_path);
			return (i);
		}
		free(full_path);
		i++;
	}
	return (-1);
}

static char	*ft_one(char **s, t_data *data)
{
	ft_parse_error(*s, ":command not found");
	data->exitstatus = 127;
	free(*s);
	return (NULL);
}

static char	*ft_two(char *tmp, char **paths, char *s, bool *free_path)
{
	char	*path;
	int		right_path;

	tmp = ft_strjoin("/", s, NULL);
	right_path = find_right_path(paths, tmp);
	if (right_path != -1)
	{
		path = ft_strjoin(paths[right_path], tmp, NULL);
		*free_path = true;
	}
	else
		path = s;
	free(tmp);
	return (path);
}

static char	*ft_three(char **s, t_data *data, char **paths)
{
	ft_parse_error(*s, ": command not found");
	data->exitstatus = 127;
	free(*s);
	if (paths)
		free_2d_array(paths);
	return (NULL);
}

/**
 * 	@brief	checks if typed-in command is valid
 * 	@param	s: pointer to literal token string of type COMMAND
 * 	@return path to the command e.g. "/bin/ls"
 * 			NULL if no command found
 * 	@NOTE	I removed type != ENVAR conditions but it has no effect whatsoever
 */
char	*type_command(char **s, t_data *data)
{
	bool	free_path;
	char	**paths;
	char	*path;
	char	*tmp;

	path = *s;
	tmp = find_env_var_value(data, "PATH");
	if (!tmp)
		return (ft_one(s, data));
	paths = ft_split(tmp, ':');
	free_path = false;
	if (s[0][0] != '/')
		path = ft_two(tmp, paths, *s, &free_path);
	if (access(path, F_OK) != 0)
	{
		if (free_path)
			free(path);
		return (ft_three(s, data, paths));
	}
	if (free_path == false)
		path = ft_strdup(*s);
	free(*s);
	free_2d_array(paths);
	return (path);
}
