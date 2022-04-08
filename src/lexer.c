#include "../include/minishell.h"

/*	split command line
 *	into tokens
 *	@params	command line
 *	@return	1 on success
 */
int	lexer(char *line)
{
	char	**tokens;
	int		count;

	if (!line)
		return (0);
	tokens = ft_split(line, ' ');
	count = 0;
	while (tokens[count])
	{
		printf("%s\n", tokens[count]);
		count++;
	}
	while (count >= 0)
	{
		free(tokens[count]);
		count--;
	}
	free(tokens);
	return (1);
}
