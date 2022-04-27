#include "../include/minishell.h"

/*	get current file
 */
static char	*get_file(void)
{
	char	*file;
	char	*dir;
	char	**split_dir;
	int		i;

	dir = getcwd(NULL, 0);
	split_dir = ft_split(dir, '/');
	i = 0;
	while (split_dir[i])
		i++;
	i--;
	file = ft_strjoin("-", split_dir[i]);
	while (i >= 0)
	{
		free(split_dir[i]);
		i--;
	}
	free(split_dir);
	free(dir);
	return (file);
}

/*	get username + current directory
 *	to be used as prompt
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
	prompt = ft_strjoin(username, file);
	promptline = NULL;
	if (status == 1)
		promptline = ft_strjoin(prompt, "\e[1;33m 42 \e[0m");
	else
		promptline = ft_strjoin(prompt, "\e[1;35m 42 \e[0m");
	free(file);
	free(prompt);
	free(username);
	return (promptline);
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
	data = malloc(sizeof(t_data));
	if (!data)
		ft_error(strerror(errno));
	while (status)
	{
		promptline = msh_prompt(status);
		data->line = readline(promptline);
		free(promptline);
		data->env_list = env_list;
		if (ft_check_EOF(data->line) && ft_strlen(data->line))
		{
			add_history(data->line);
			data->tokens = msh_lexer(data->line);
			data->command = msh_parser(data->tokens);
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
	init_signal_handling();
	msh_loop(envp);
	return (EXIT_SUCCESS);
}
