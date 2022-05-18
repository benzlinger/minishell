#include "../include/minishell.h"

//echo " and echo "' leak

/**	@brief	get current file
 *	@return	current file
 */
static char	*get_file(void)
{
	char	*file;
	char	*dir;
	char	**split_dir;
	int		i;

	dir = getcwd(NULL, 0);
	if (!dir)
		ft_error(strerror(errno));
	if (!ft_strncmp(dir, "/", ft_strlen(dir) + 1))
		file = ft_strdup("/");
	else
	{
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
	}
	free(dir);
	return (file);
}

/**	@brief	get username + current directory to be used as prompt
 *	@param	status of shell (for colouring)
 *	@return	prompt for shell
 */
static char	*msh_prompt(t_data *data)
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

static t_data	*init_data(char **env_list)
{
	t_data	*data;
	char	*name;
	char	*value;

	data = malloc(sizeof(t_data));
	if (!data)
		ft_error(strerror(errno));
	if (env_list && env_list[0])
		data->vars = init_vars(env_list);
	else
	{
		name = ft_strdup("minishell");
		value = ft_strdup("rsiebertandbtenzlin");
		data->vars = new_var(name, value);
	}
	if (!data->vars)
		ft_exec_error("Init failed.", NULL);
	data->env_list = env_list;
	data->exitstatus = 0;
	data->status = 1;
	data->err_color = 0;
	return (data);
}

/*	Basic loop of a shell
 *	1. Read the command from stdin
 *	2. Separate the command string into a programm and arguments
 *	3. Run the parsed command
 */
static void	msh_loop(t_data *data)
{
	int		status;
	char	*promptline;

	status = 1;
	while (status)
	{
		promptline = msh_prompt(data);
		data->line = readline(promptline);
		free(promptline);
		if (ft_check_eof(data->line) && ft_strlen(data->line))
		{
			add_history(data->line);
			data->tokens = msh_lexer(data->line);
			data->command = msh_parser(data);
			if (data->command != NULL)
			{
				status = pipe_exec(data);
				free(data->command);
			}
			ft_free_tokens(&data->tokens);
		}
		else
			data->err_color = 1;
		free(data->line);
	}
	free_vars(data->vars);
	free(data);
}

/*	1. Loading config files (if any)
 *	2. Command loop
 *	3. Shutdown/Cleanup
 */
int	main(int argc, char *argv[], char *envp[])
{
	t_data	*data;

	if (argc != 1)
		ft_error(strerror(E2BIG));
	argv = NULL;
	// envp = NULL;
	data = init_data(envp);
	init_signal_handling(data->exitstatus); //on ctrl+c exit status should be 1
	msh_loop(data);
	return (EXIT_SUCCESS);
}
