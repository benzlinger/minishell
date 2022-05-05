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
static char	*msh_prompt(int status)
{
	char	*file;
	char	*prompt;
	char	*promptline;
	char	*username;

	file = get_file();
	file = ft_color_format_str(file, "\e[36m", &file);
	username = ft_color_format_str(getenv("USER"), "\e[1;36m", NULL);
	prompt = ft_strjoin(username, file, NULL);
	promptline = NULL;
	if (status == 1)
		promptline = ft_strjoin(prompt, "\e[1;33m 42 \e[0m", NULL);
	else
		promptline = ft_strjoin(prompt, "\e[1;35m 42 \e[0m", NULL);
	free(file);
	free(prompt);
	free(username);
	return (promptline);
}

static t_data	*init_data(char **env_list)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		ft_error(strerror(errno));
	data->vars = init_vars(env_list);
	if (!data->vars)
		ft_exec_error("Init failed.", NULL);
	data->env_list = env_list;
	data->exitstatus = 0;
	return (data);
}

/*	Basic loop of a shell
 *	1. Read the command from stdin
 *	2. Separate the command string into a programm and arguments
 *	3. Run the parsed command
 */
static void	msh_loop(char **env_list)
{
	t_data	*data;
	int		status;
	char	*promptline;

	status = 1;
	data = init_data(env_list);
	while (status)
	{
		promptline = msh_prompt(status);
		data->line = readline(promptline);
		free(promptline);
		if (ft_check_eof(data->line) && ft_strlen(data->line))
		{
			add_history(data->line);
			data->tokens = msh_lexer(data->line);
			data->command = msh_parser(data);
			//if command == NULL a parse error occured and a new
			//prompt will be displayed
			if (data->command != NULL)
			{
				status = msh_executer(data);
				free(data->command);
			}
			ft_free_tokens(&data->tokens);
		}
		free(data->line);
	}
	free_vars(data->vars);
	free(data);
	// system("leaks minishell");
	//TODO: ft_exit
}

/*	1. Loading config files (if any)
 *	2. Command loop
 *	3. Shutdown/Cleanup
 */
int	main(int argc, char *argv[], char *envp[])
{
	if (argc != 1)
		ft_error(strerror(E2BIG));
	argv = NULL;
	init_signal_handling(); //on ctrl+c exit status should be 1
	msh_loop(envp);
	return (EXIT_SUCCESS);
}
