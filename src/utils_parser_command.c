#include "../include/minishell.h"

static bool	contains_path(char **paths, char *pth)
{
	int	i;

	i = 0;
	while (pth[i] != '/' && pth[i])
		i++;
	if (i == (int)ft_strlen(pth))
		return (false);
	i = ft_strlen(pth);
	while (pth[i] != '/')
	{
		pth[i] = '\0';
		i--;
	}
	pth[i] = '\0';
	i = 0;
	while (paths[i])
	{
		printf("paths[%i]:\t%s\npth:\t\t%s\n", i, paths[i], pth);
		if (ft_strncmp(paths[i], pth, ft_strlen(pth)) == 0)
			return (true);
		i++;
	}
	return (false);
}

/**
 * 	@brief	checks if typed-in command is valid
 * 	@param	s: pointer to literal token string of type COMMAND
 * 	@return path to the command e.g. "/bin/ls"
 * 		NULL if no command found
 */
char	*type_command(char **s, int type)
{
	char	*right_path;
	char	*path;
	bool	free_path;
	char	**paths;

	path = *s;
	// TODO free
	paths = ft_split(getenv("PATH"), ':');
	free_path = false;
	printf("%d\n",contains_path(paths, path));
	if (!contains_path(paths, path))
	{
		path = *s;
		// TODO LEFT OF HERE
		right_path = find_right_path(paths, path)
		tmp = ft_strdup("/bin/");
		path = ft_strjoin(tmp, *s);
		free_path = true;
		free(tmp);
	}
	if (access(path, F_OK) != 0)
	{
		ft_parse_error(*s, ": command not found");
		if (type != ENVAR)
			free(*s);
		if (free_path)
			free(path);
		return (NULL);
	}
	if (type != ENVAR)
		free(*s);
	return (path);
}
