#include "../include/minishell.h"

/**
 * 	@brief	checks if string is one of the builtins
 * 	@param	s: literal (token)string of command prompt
 * 	@return true if s equals one of the builtins
 */
static bool	check_builtins(char *s)
{
	if (ft_strncmp(s, "echo", ft_strlen("echo")) == 0)
		return (true);
	else if (ft_strncmp(s, "cd", ft_strlen("cd")) == 0)
		return (true);
	else if (ft_strncmp(s, "pwd", ft_strlen("pwd")) == 0)
		return (true);
	else if (ft_strncmp(s, "export", ft_strlen("export")) == 0)
		return (true);
	else if (ft_strncmp(s, "unset", ft_strlen("unset")) == 0)
		return (true);
	else if (ft_strncmp(s, "env", ft_strlen("env")) == 0)
		return (true);
	else if (ft_strncmp(s, "exit", ft_strlen("exit")) == 0)
		return (true);
	else
		return (false);
}

/**
 * 	@brief	figures out the classification of a token
 *	@param	literal: literal (token)string of command prompt
 *	@return	enumarated clasification (int)
 */
int ft_get_type(char *literal)
{
	if (check_builtins(literal))
		return (BUILTIN);
	else if (literal[0] == '-')
		return (FLAG);
	else if (literal[0] == 39)
		return (SQUOTE);
	else if (literal[0] == '"')
		return (DQUOTE);
	else if (literal[0] == '<' || literal [0] == '>')
		return (REDIREC);
	else if (literal[0] == '|')
		return (PIPE);
	else if (ft_strncmp(literal, "$USER", ft_strlen("$USER")) == 0)
		return (ENVARU);
	else if (literal[0] == '$')
		return (ENVAR);
	return (UNKNOWN);
}

/**
 * 	@brief	checks for EOF "signal" from ctrl+D and
 * 		exits the programm if an EOF was detected
 * 		also check if string is only space ' '
 * 	@param	s: string from readline
 * 	@return	true is returned if s is not NULL (no EOF detected)
 * 		true if string is not only space ' '
 */
bool	ft_check_EOF(char *s)
{
	int	i;

	if (s == NULL)
		ft_exit(EOF);
	i = 0;
	while (s[i])
	{
		if (s[i] != ' ')
			return (true);
		i++;
	}
	return (false);
}

/**
 * 	@brief	gets the pipe_index for the tokens starting by 0
 *		first occuring pipe also gets pipe_index == 0
 *		second one gets pipe_index == 1 etc.
 *	@param	prompt:	command line prompt
 *	@param	pos: index of token in command line prompt (position)
 *	@return	the pipe_index
 */
int	ft_get_pipe_index(char **prompt, int pos)
{
	int	i;
	int	pipe_count;

	i = 0;
	pipe_count = 0;
	while (i < pos)
	{
		if (prompt[i][0] == '|' && prompt[i][1] == '\0')
			pipe_count++;
		i++;
	}
	return (pipe_count);
}
