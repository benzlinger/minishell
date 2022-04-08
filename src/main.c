#include "../include/minishell.h"

/*	print username + current directory
 *	to be used as prompt
 */
void	msh_dir(void)
{
	char	cwd[1024];
	char	**split_dir;
	char	*username;
	int		count;

	getcwd(cwd, sizeof(cwd));
	split_dir = ft_split(cwd, '/');
	count = 0;
	while (split_dir[count])
		count++;
	count--;
	username = getenv("USER");
	printf("%s %s", username, split_dir[count]);
	while (count >= 0)
	{
		free(split_dir[count]);
		count--;
	}
	free(split_dir);
}

/*	Basic loop of a shell
 *	1. Read the command from stdin
 *	2. Separate the command string into a programm and arguments
 *	3. Run the parsed command
 */
static void	msh_loop(void)
{
	char	*line;
	char	**tokens;
	char	*command;
	int	status;

	status = 1;
	while (status)
	{
		msh_dir();
		line = readline(" % ");
		if (ft_strlen(line))
		{
			add_history(line);
			lexer(line);
		}
		// else //to check for leaks
		// 	status = 0;

		// TODO lexer, parser, executer
		//tokens = msh_lexer(line);
		//command = msh_parser(tokens);
		//status = msh_execute(command);
		free(line);
		//free(tokens);
		//free(command);
	}
}

/*	1. Loading config files (if any)
 *	2. Command loop
 *	3. Shutdown/Cleanup
 */
int	main(int argc, char *argv[])
{
	msh_loop();
	// while (1) //to check for leaks
	// 	pause();
	return (EXIT_SUCCESS);
}
