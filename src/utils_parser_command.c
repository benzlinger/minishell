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

char	*find_env_var_value(t_data *data, char *name)
{
	t_vars	*current;

	current = data->vars;
	while (current)
	{
		if (!ft_strncmp(current->name, name, ft_strlen(name) + 1)
			&& current->value)
			return (current->value);
		current = current->next;
	}
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
	int		right_path;
	bool	free_path;
	char	**paths;
	char	*path;
	char	*tmp;

	path = *s;
	// paths = ft_split(getenv("PATH"), ':');
	tmp = find_env_var_value(data, "PATH");
	if (!tmp)
	{
		ft_parse_error(*s, ": command not found");
		free(*s);
		return (NULL);
	}
	paths = ft_split(tmp, ':');
	tmp = NULL;
	free_path = false;
	if (s[0][0] != '/')
	{
		tmp = ft_strjoin("/", *s, NULL);
		right_path = find_right_path(paths, tmp);
		if (right_path != -1)
		{
			path = ft_strjoin(paths[right_path], tmp, NULL);
			free_path = true;
		}
		free(tmp);
	}
	if (access(path, F_OK) != 0)
	{
		ft_parse_error(*s, ": command not found");
	//	if (type != ENVAR)
	//		free(*s);
		free(*s);
		if (free_path)
			free(path);
		if (paths)
			free_2d_array(paths);
		return (NULL);
	}
	if (free_path == false)
		path = ft_strdup(*s);
	//if (type != ENVAR)
	//	free(*s);
	free(*s);
	free_2d_array(paths);
	return (path);
}
