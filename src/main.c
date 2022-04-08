#include "../include/minishell.h"

/*	print current directory
 *	to be used as prompt
*/
void	msh_dir(void)
{
	char	cwd[1024];

	getcwd(cwd, sizeof(cwd));
	printf("%s", cwd);
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
		line = readline("> ");

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
	return (EXIT_SUCCESS);
}
