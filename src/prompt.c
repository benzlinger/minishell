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

static void	free_prompt(char *file, char *prompt, char *username)
{
	free(file);
	free(prompt);
	free(username);
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
	char		*user;

	file = get_file();
	file = ft_color_format_str(file, CYAN, &file);
	user = find_env_var_value(data, "USER");
	if (!user)
		user = "no_user";
	username = ft_color_format_str(user, BCYAN, NULL);
	prompt = ft_strjoin(username, file, NULL);
	if (!g_exitstatus || data->err_color)
	{
		promptline = ft_strjoin(prompt, YELLOW" 42 "RESET, NULL);
		data->err_color = 0;
	}
	else
	{
		promptline = ft_strjoin(prompt, PURPLE" 42 "RESET, NULL);
		data->err_color = 1;
	}
	free_prompt(file, prompt, username);
	return (promptline);
}
