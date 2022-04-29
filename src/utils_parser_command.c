#include "../include/minishell.h"

static int	find_right_path(char **paths, char *command)
{
	int		i;
	char	*full_path;

	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], command);
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

/**
 * 	@brief	checks if typed-in command is valid
 * 	@param	s: pointer to literal token string of type COMMAND
 * 	@return path to the command e.g. "/bin/ls"
 * 		NULL if no command found
 */
char	*type_command(char **s, int type)
{
	int		right_path;
	bool	free_path;
	char	**paths;
	char	*path;
	char	*tmp;

	path = *s;
	paths = ft_split(getenv("PATH"), ':');
	free_path = false;
	if (s[0][0] != '/')
	{
		tmp = ft_strjoin("/", *s);
		right_path = find_right_path(paths, tmp);
		if (right_path != -1)
		{
			path = ft_strjoin(paths[right_path], tmp);
			free_path = true;
		}
		free(tmp);
	}
	if (access(path, F_OK) != 0)
	{
		ft_parse_error(*s, ": command not found");
		if (type != ENVAR)
			free(*s);
		if (free_path)
			free(path);
		if (paths)
			free_2d_array(paths);
		return (NULL);
	}
	if (free_path == false)
		path = ft_strdup(*s);
	if (type != ENVAR)
		free(*s);
	free_2d_array(paths);
	return (path);
}
