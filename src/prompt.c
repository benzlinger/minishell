#include "../include/minishell.h"

static char	*ft_one(char *dir)
{
	int		i;
	char	**split_dir;
	char	*file;

	split_dir = ft_split(dir, '/');
	i = 0;
	while (split_dir[i])
		i++;
	i--;
	file = ft_strjoin("-", split_dir[i], NULL);
	while (split_dir[i] && i >= 0)
	{
		free(split_dir[i]);
		i--;
	}
	free(split_dir);
	return (file);
}

/**
 * 	@brief	get current file
 *	@return	current file
 */
static char	*get_file(void)
{
	char	*file;
	char	*dir;

	dir = getcwd(NULL, 0);
	if (!dir)
		ft_error(strerror(errno));
	if (!ft_strncmp(dir, "/", ft_strlen(dir) + 1))
		file = ft_strdup("-/");
	else
		file = ft_one(dir);
	free(dir);
	return (file);
}

/**	
 * 	@brief	get username + current directory to be used as prompt
 *	@param	status of shell (for colouring)
 *	@return	prompt for shell
 */
char	*msh_prompt(t_data *data)
{
	char		*file;
	char		*prompt;
	char		*promptline;
	char		*username;

	file = get_file();
	file = ft_color_format_str(file, "\e[36m", &file);
	username = ft_color_format_str(getenv("USER"), "\e[1;36m", NULL);
	prompt = ft_strjoin(username, file, NULL);
	promptline = NULL;
	if (!data->exitstatus || data->err_color)
	{
		promptline = ft_strjoin(prompt, "\e[1;33m 42 \e[0m", NULL);
		data->err_color = 0;
	}
	else
	{
		promptline = ft_strjoin(prompt, "\e[1;95m 42 \e[0m", NULL);
		data->err_color = 1;
	}
	free(file);
	free(prompt);
	free(username);
	return (promptline);
}
