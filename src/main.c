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
static char	*msh_prompt(void)
{
	char	*file;
	char	*prompt;
	char	*promptline;

	file = get_file();
	prompt = ft_strjoin(getenv("USER"), file);
	promptline = ft_strjoin(prompt, " % ");
	free(file);
	free(prompt);
	return (promptline);
}

/*	Basic loop of a shell
 *	1. Read the command from stdin
 *	2. Separate the command string into a programm and arguments
 *	3. Run the parsed command
 */
static void	msh_loop(void)
{
	t_token_list	*tokens;
	char		*line;
	char		*command;
	int		status;
	char		*promptline;

	status = 1;
	while (status)
	{
		promptline = msh_prompt();
		line = readline(promptline);
		free(promptline);
		if (ft_check_EOF(line) && ft_strlen(line))
		{
			add_history(line);
			tokens = msh_lexer(line);
			command = msh_parser(tokens);
			//if command == NULL a parse error occured and a new
			//prompt will be displayed
			if (command != NULL)
			{
				status = msh_executer(command);
				free(command);
			}
			ft_free_tokens(&tokens);
		}
		free(line);
	}
}

/*	1. Loading config files (if any)
 *	2. Command loop
 *	3. Shutdown/Cleanup
 */
int	main(int argc, char *argv[])
{
	if (argc != 1)
		ft_error(strerror(E2BIG));
	init_signal_handling();
	msh_loop();
	return (EXIT_SUCCESS);
}
